#include "soundeffect.h"
#include <data.h>


const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);


AudioSource::~AudioSource()
{
    if (pcmAudio)
    {
        delete[] pcmAudio;
    }
}


void AudioSource::refresh()
{
    initialised = false;
    pcmPos = 0;
}


void AudioSource::init()
{
    pcmPos = 0;
    pcmAudio = new float[sampleCount];
    const float radsPerSec = 2 * 3.1415926536 * frequency / (float)format.Format.nSamplesPerSec;
    for (unsigned long i = 0; i < sampleCount; i++)
    {
        float sampleValue = sin(radsPerSec * (float)i);
        pcmAudio[i] = sampleValue;
    }
    initialised = true;
}


HRESULT AudioSource::SetFormat(WAVEFORMATEX* wfex)
{
    if (wfex->wFormatTag == WAVE_FORMAT_EXTENSIBLE)
    {
        format = *reinterpret_cast<WAVEFORMATEXTENSIBLE*>(wfex);
    }
    else
    {
        format.Format = *wfex;
        format.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
        INIT_WAVEFORMATEX_GUID(&format.SubFormat, wfex->wFormatTag);
        format.Samples.wValidBitsPerSample = format.Format.wBitsPerSample;
        format.dwChannelMask = 0;
    }
    const UINT16 formatTag = EXTRACT_WAVEFORMATEX_ID(&format.SubFormat);

    return 0;
}


HRESULT AudioSource::LoadData(UINT32 totalFrames, BYTE* dataOut, DWORD* flags)
{
    float* fData = (float*)dataOut;
    UINT32 totalSamples = totalFrames * format.Format.nChannels ;
    if (!initialised)
    {
        init();
        bufferSize = totalFrames * format.Format.nChannels;
    }
    if (pcmPos < sampleCount)
    {
        for (UINT32 i = 0; i < totalSamples; i += format.Format.nChannels)
        {
            for (size_t chan = 0; chan < format.Format.nChannels; chan++)
            {
                fData[i + chan] = (pcmPos < sampleCount) ? pcmAudio[pcmPos] : 0.0f;
            }
            pcmPos++;
        }
        bufferPos += totalSamples;
        bufferPos %= bufferSize;
    }
    else
    {
        refresh();
    }

    return 0;
}


AudioStream::AudioStream() {

    IMMDeviceEnumerator* pEnumerator;
    IMMDevice* pDevice;

    hnsRequestedDuration = REFTIMES_PER_SEC;
    hnsActualDuration;
    pAudioClient = NULL;
    pRenderClient = NULL;
    pwfx = NULL;

    hr = CoInitialize(nullptr);

    hr = CoCreateInstance(CLSID_MMDeviceEnumerator,
        NULL,
        CLSCTX_ALL, IID_IMMDeviceEnumerator,
        (void**)&pEnumerator);
    EXIT_ON_ERROR(hr);

    hr = pEnumerator->GetDefaultAudioEndpoint(
        eRender, eConsole, &pDevice);
    EXIT_ON_ERROR(hr);

    hr = pDevice->Activate(
        IID_IAudioClient, CLSCTX_ALL,
        NULL, (void**)&pAudioClient);
    EXIT_ON_ERROR(hr);

    hr = pAudioClient->GetMixFormat(&pwfx);
    EXIT_ON_ERROR(hr);

    hr = pAudioClient->IsFormatSupported(AUDCLNT_SHAREMODE_EXCLUSIVE, pwfx, &pClosestMatch);

    hr = pAudioClient->Initialize(
        AUDCLNT_SHAREMODE_SHARED,
        AUDCLNT_STREAMFLAGS_EVENTCALLBACK,
        hnsRequestedDuration,
        hnsRequestedDuration,
        pwfx,
        NULL);
    EXIT_ON_ERROR(hr);

    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hEvent == NULL)
    {
        hr = E_FAIL;
        goto Exit;
    }

    hr = pAudioClient->SetEventHandle(hEvent);
    EXIT_ON_ERROR(hr);

    hr = pAudioClient->GetBufferSize(&bufferFrameCount);
    EXIT_ON_ERROR(hr);

    hr = pAudioClient->GetService(
        IID_IAudioRenderClient,
        (void**)&pRenderClient);
    EXIT_ON_ERROR(hr);

    hr = SoundEffects::setSoundsFormats(pwfx);
    EXIT_ON_ERROR(hr);


    SAFE_RELEASE(pEnumerator);
    SAFE_RELEASE(pDevice);

    hr = pAudioClient->Start();
    EXIT_ON_ERROR(hr);


Exit:
    CoTaskMemFree(pwfx);
}


AudioStream::~AudioStream() {

    CoTaskMemFree(pwfx);
    hr = pAudioClient->Stop();
    SAFE_RELEASE(pAudioClient);
    SAFE_RELEASE(pRenderClient);
    CoUninitialize();
}


HRESULT AudioStream::playAudio(AudioSource* audioSource) {


    hr = pRenderClient->GetBuffer(bufferFrameCount, &pData);
    EXIT_ON_ERROR(hr);

    hr = audioSource->LoadData(bufferFrameCount, pData, &flags);
    EXIT_ON_ERROR(hr);

    hr = pRenderClient->ReleaseBuffer(bufferFrameCount, flags);
    EXIT_ON_ERROR(hr);


Exit:
    return hr;

}

#pragma once
#include <vector>
#include <queue>
#include <list>
#include <soundeffect.h>
#include <map>
#include <unordered_map>
#include <QKeyEvent>



#define PIXEL_FONT_PATH "assets/PressStart2P-Regular.ttf"

#define FONT \
		([]() -> QFont { \
			int fontId = QFontDatabase::addApplicationFont(PIXEL_FONT_PATH); \
			if (fontId != -1) { \
				QString pixelFont = QFontDatabase::applicationFontFamilies(fontId).at(0); \
				return QFont(pixelFont, 10, QFont::Bold); \
			} else { \
				QFont("Arial", 15, QFont::Bold); \
			} \
		}())


/// <summary>
/// Klasa reprezentująca dane sprzężone z klawiaturą.
/// </summary>
class KeyboardData
{
public:

	/// <summary>
	/// Metoda statyczna zwracająca wartość true, jeżeli przekazane do funkcji ID klawisza znajduje się w zbiorze 
	/// klawiszy oznaczonych jako funkcjonalne (wykorzystywane np. w wyborze w menu). W przeciwnym razie zwraca 
	/// wartość false.
	/// </summary>
	/// <param name=keyID> ID klawisza </param>
	static bool isFunctionalKeyPressed(int keyID);


	/// <summary>
	/// Wektor zawierający ID klawiszy wykorzystywanych w celach specjalnych, np. do obsługi menu lub zapisu 
	/// nagranego dźwięku.
	/// </summary>
	static std::vector<int> functionalKeysUsed; 

	/// <summary>
	/// Mapa pełniąca funkcję słownika <obiekt_dźwiękowy - id_klawisza>.
	/// </summary>
	static std::map<int, std::pair<AudioSource*, int>> soundToKeyDictionary;

	/// <summary>
	/// Metoda statyczna zwracająca obiekt dźwiękowy przypisany do danego klawisza.
	/// </summary>
	/// <param name=keyID> ID klawisza </param>
	static AudioSource* getAudio(int keyID);

	/// <summary>
	/// Metoda statyczna zamieniająca klawisz przypisany do określonego obiektu dźwiękowego na klawisz określony 
	/// poprzez wyznaczone ID. Obiekt dźwiękowy wybrany na podstawie indeksu ze struktury soundToKeyDictionary.
	/// </summary>
	/// <param name=selectedSoundOption> Indeks wskazujący na obiekt dźwiękowy w strukturze. </param>
	/// <param name=keyID> ID klawisza. </param>
	static void changeKeyOfSelectedSound(int selectedSoundOption, int keyID);

	/// <summary>
	/// Metoda statyczna sprawdzająca czy klawisz o określonym ID jest już w użyciu.
	/// </summary>
	/// <param name=keyID> ID klawisza. </param>
	static bool isKeyUsed(int keyID);

	/// <summary>
	/// Zmienna logiczna zwracająca wartość true dla trwającej zmiany klawisza przypisanego do dźwięku na inny.
	/// </summary>
	static bool changeSoundKeyValue;

private:

	/// <summary>
	/// Metoda statyczna sprawdzająca czy klawisz o określonym ID jest już w użyciu.
	/// </summary>
	/// <param name=keyID> ID klawisza. </param>
	static std::pair<AudioSource*, int> getPairByKeyID(int keyID);


};


/// <summary>
/// Klasa reprezentująca dane sprzężone z dźwiękami i nutami.
/// </summary>
class NoteData
{
public:
	/// <summary>
	/// Zmienna logiczna przechowująca wartość true podczas nagrywania dźwięku, w przeciwnym wypadku 
	/// przechowuje wartość false.
	/// </summary>
	static bool recordingAudio;

	/// <summary>
	/// Metoda statyczna zmieniająca wartość zmiennej recordingAudio na przeciwną jeżeli zostaną 
	/// spełnione określone warunki.
	/// </summary>
	static void toggleRecordingAudio();

	/// <summary>
	/// Metoda statyczna zwracająca wartość zmiennej recordingAudio.
	/// </summary>
	static bool isRecordingAudio() { return recordingAudio; }

	/// <summary>
	/// Metoda statyczna zwracająca obiekt dźwiękowy określonego klawisza.
	/// </summary>
	/// <param name=qtKey> ID klawisza. </param>
	static AudioSource* getSound(int qtKey);

	/// <summary>
	/// Słownik <id_klawisza - obiekt_dźwiękowy>.
	/// </summary>
	static std::unordered_map<int, AudioSource*> keyToNoteDictionary;

	/// <summary>
	/// Słownik <obiekt_dźwiękowy - pozycja_nutki>.
	/// </summary>
	static std::unordered_map<AudioSource*, int> const soundToPositionDictionary;

	/// <summary>
	/// Wskaźnik na kolejke zawierającą kolejne dźwięki wraz z ich czasem trwania w nagranej sekwencji.
	/// </summary>
	static std::queue<std::pair<AudioSource*, int>>* recordedAudioBuffer;

	/// <summary>
	/// Wskaźnik na wektor zawierający zapisane nagrania.
	/// </summary>
	static std::vector<std::queue<std::pair<AudioSource*, int>>*>* recordedTracks;

	/// <summary>
	/// Metoda statyczna zapisująca nagrany dźwięk do wektora.
	/// </summary>
	static void saveRecordedAudio();

	/// <summary>
	/// Metoda statyczna zwracająca częstotliwość dźwięku danego obiektu na podstawie ID przypisanego do niego 
	/// klawisza.
	/// </summary>
	static int getSoundFrequency(int qtKey);

	/// <summary>
	/// Metoda statyczna zwracająca ciągi znaków w postaci "symbol_dźwięku - symbol_klawisza".
	/// </summary>
	static std::vector<std::string>* getSoundToKeyStrings();
};


/// <summary>
/// Klasa reprezentująca dane sprzężone z opcjami menu.
/// </summary>
class OptionsData
{
public:
	/// <summary>
	/// Iterator listy layoutów przypisanych do menu programu.
	/// </summary>
	static std::list<int>::iterator layoutIterator;

	/// <summary>
	/// Lista layoutów menu głównego programu reprezentowana przez wartosci liczbowe.
	/// </summary>
	static std::list<int> menuLayoutsOptions;

	/// <summary>
	/// Lista możliwych do wyboru opcji dla pierwszego layoutu menu głównego reprezentowana przez 
	/// wartosci liczbowe.
	/// </summary>
	static std::list<int> mainMenuOptions;

	/// <summary>
	/// Lista możliwych do wyboru opcji dla drugiego layoutu menu głównego reprezentowana przez 
	/// wartosci liczbowe.
	/// </summary>
	static std::list<int> recordAudioOptions;

	/// <summary>
	/// Lista możliwych do wyboru opcji dla trzeciego layoutu menu głównego reprezentowana przez 
	/// wartosci liczbowe.
	/// </summary>
	static std::list<int> audioMenuOptions;

	/// <summary>
	/// Lista możliwych do wyboru opcji dla czwartego layoutu menu głównego reprezentowana przez 
	/// wartosci liczbowe.
	/// </summary>
	static std::list<int> soundKeyMenuOptions;
};


/// <summary>
/// Klasa reprezentująca słownik <id_klawisza - symbol_klawisza>.
/// </summary>
class KeyStringDictionary
{
public:
	/// <summary>
	/// Słownik <id_klawisza - symbol_klawisza>.
	/// </summary>
	static std::unordered_map<int, std::string> const keyStringDictionary;
};


/// <summary>
/// Klasa reprezentująca dźwięki poprzez symbole nutowe.
/// </summary>
class SoundEffects
{
public:
	/// <summary>
	/// Metoda statyczna ustawiająca format dla wszystkich źródeł dźwięków tej klasy.
	/// </summary>
	/// <param name=format> Format dźwięku. </param>
	static HRESULT setSoundsFormats(WAVEFORMATEX* format);

	/// <summary>
	/// Źródło dźwięku C2.
	/// </summary>
	static AudioSource* soundC2;

	/// <summary>
	/// Źródło dźwięku D2.
	/// </summary>
	static AudioSource* soundD2;

	/// <summary>
	/// Źródło dźwięku E2.
	/// </summary>
	static AudioSource* soundE2;

	/// <summary>
	/// Źródło dźwięku F2.
	/// </summary>
	static AudioSource* soundF2;

	/// <summary>
	/// Źródło dźwięku G2.
	/// </summary>
	static AudioSource* soundG2;

	/// <summary>
	/// Źródło dźwięku A2.
	/// </summary>
	static AudioSource* soundA2;

	/// <summary>
	/// Źródło dźwięku B2.
	/// </summary>
	static AudioSource* soundB2;

	/// <summary>
	/// Źródło dźwięku C3.
	/// </summary>
	static AudioSource* soundC3;

	/// <summary>
	/// Źródło dźwięku D3.
	/// </summary>
	static AudioSource* soundD3;

	/// <summary>
	/// Źródło dźwięku E3.
	/// </summary>
	static AudioSource* soundE3;

	/// <summary>
	/// Źródło dźwięku F3.
	/// </summary>
	static AudioSource* soundF3;

	/// <summary>
	/// Źródło dźwięku G3.
	/// </summary>
	static AudioSource* soundG3;

	/// <summary>
	/// Źródło dźwięku A3.
	/// </summary>
	static AudioSource* soundA3;

	/// <summary>
	/// Źródło dźwięku B3.
	/// </summary>
	static AudioSource* soundB3;

	/// <summary>
	/// Źródło dźwięku C4.
	/// </summary>
	static AudioSource* soundC4;

	/// <summary>
	/// Źródło dźwięku D4.
	/// </summary>
	static AudioSource* soundD4;

	/// <summary>
	/// Źródło dźwięku E4.
	/// </summary>
	static AudioSource* soundE4;

	/// <summary>
	/// Źródło dźwięku F4.
	/// </summary>
	static AudioSource* soundF4;

	/// <summary>
	/// Źródło dźwięku G4.
	/// </summary>
	static AudioSource* soundG4;

	/// <summary>
	/// Źródło dźwięku A4.
	/// </summary>
	static AudioSource* soundA4;

	/// <summary>
	/// Źródło dźwięku B4.
	/// </summary>
	static AudioSource* soundB4;

	/// <summary>
	/// Źródło dźwięku C5.
	/// </summary>
	static AudioSource* soundC5;

	/// <summary>
	/// Źródło dźwięku D5.
	/// </summary>
	static AudioSource* soundD5;

	/// <summary>
	/// Źródło dźwięku E5.
	/// </summary>
	static AudioSource* soundE5;

	/// <summary>
	/// Źródło dźwięku F5.
	/// </summary>
	static AudioSource* soundF5;

	/// <summary>
	/// Źródło dźwięku G5.
	/// </summary>
	static AudioSource* soundG5;

	/// <summary>
	/// Źródło dźwięku A5.
	/// </summary>
	static AudioSource* soundA5;

	/// <summary>
	/// Źródło dźwięku B5.
	/// </summary>
	static AudioSource* soundB5;

	/// <summary>
	/// Źródło dźwięku C6.
	/// </summary>
	static AudioSource* soundC6;
};
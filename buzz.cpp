
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
using namespace std;
using namespace sf;

//Initializing Dimensions.
//resolutionX and resolutionY determine the rendering resolution.

const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; //Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; //Total columns on grid

//Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                      FUNCTIONS DECLERATIONS                             //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite,int& canCount,int& spraysUsedInCurrentCan,const int SPRAYS_PER_CAN,const int SPRAYS_PER_LEVEL,Font font);

void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);

void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);

void playerMovement(float& player_x, float& player_y, Clock& delayTime, Keyboard& key,bool flowersInLastTier[]);

void Menu(RenderWindow& window, Music& bgMusic, bool& startGame, Font& font, Sprite& menuSprite, std::string highScoreNames[], int highScores[], const int MAX_HIGH_SCORES,std::string& playerName);

void drawworkerBee(RenderWindow& window,Sprite workerBeeSprite [],const int maxWorkerBee,bool Workerbee_exists[]);

void moveWorkerBee(RenderWindow& window,Sprite workerBeeSprite[],const int maxWorkerBee,bool Workerbee_exists[],float workerBee_x[],float workerBee_y[],bool workerBeemovingRight[],Clock workerBeeClocks[],float workerBeeSpeeds[],Clock& workerBeespawnClock,int& workerBeenextSpawnTime,int& totalworkerBeesSpawned,bool workerBeestopped[],float workerBeestopTime[],Clock workerBeeStopClocks[],int workerBeestopCount[],int workerBeemaxStops[],bool& firstBeeFlowerDone,bool flowersInLastTier[],Sprite flowerSprites[]);

void collisionDetection(float& bullet_x, float& bullet_y, bool& bullet_exists,const int maxWorkerBee,bool Workerbee_exists[],float workerBee_x[],float workerBee_y[],Sprite workerbeehoneycombSprites[],const int maxWorkerbeehoneycombs,float workerbeehoneycomb_x[],float workerbeehoneycomb_y[],bool workerbeehoneycomb_exists[],bool workerBeemovingRight[],Sprite workerBeeSprite[],const int maxKillerBees,const int maxRedHoneycombs,float redHoneycomb_x[],float redHoneycomb_y[],bool redHoneycomb_exists[],Sprite red_honeycombSprites[],float killerBee_x[],float killerBee_y[],bool killerBee_exists[],int& score);

void drawworkerbeehoneycomb(RenderWindow& window,const int maxWorkerbeehoneycombs,bool workerbeehoneycomb_exists[],Sprite workerbeehoneycombSprites[]);

void drawKillerBee(RenderWindow& window,const int maxKillerBees,bool killerBee_exists[],Sprite killerBeeSprites[]);

void moveKillerBee(const int maxKillerBees,float killerBee_x[],float killerBee_y[],bool killerBee_exists[],bool killerBee_movingRight[],Clock killerBeeClocks[],float killerBeeSpeeds[],Clock& killerBeeSpawnClock,int& nextKillerBeeSpawnTime,int& totalKillerBeesSpawned,Sprite killerBeeSprites[],bool& firstBeeFlowerDone,bool flowersInLastTier[],Sprite flowerSprites[]);

void drawRedHoneycombs(RenderWindow& window,const int maxRedHoneycombs,float redHoneycomb_x[],float redHoneycomb_y[],bool redHoneycomb_exists[],Sprite red_honeycombSprites[]);

void initializeHummingbird(float& hummingbird_x, float& hummingbird_y, bool& hummingbird_exists, bool& hummingbird_sick, int& hummingbird_health, bool& hummingbird_flapOpen, bool& hummingbird_paused,int& hummingbird_direction, float& hummingbirdSpeed,Clock& hummingbirdDirectionClock, Clock& hummingbirdAnimationClock, Clock& hummingbirdPauseClock, Clock& hummingbirdRespawnClock,Texture& hummingbirdTexture, Sprite& hummingbirdSprite,const int HUMMINGBIRD_RIGHT);

void drawHummingbird(RenderWindow& window, bool hummingbird_exists, Sprite& hummingbirdSprite);

void moveHummingbird(float& hummingbird_x, float& hummingbird_y, bool& hummingbird_exists, bool& hummingbird_sick, int& hummingbird_health, bool& hummingbird_paused, float& hummingbird_pauseDuration,int& hummingbird_direction, float hummingbirdSpeed,Clock& hummingbirdDirectionClock, Clock& hummingbirdAnimationClock, Clock& hummingbirdPauseClock, Clock& hummingbirdRespawnClock,bool& hummingbird_flapOpen, Sprite& hummingbirdSprite,const int HUMMINGBIRD_LEFT,const int HUMMINGBIRD_RIGHT,const int HUMMINGBIRD_UP,const int HUMMINGBIRD_DOWN,const int HUMMINGBIRD_UP_LEFT ,const int HUMMINGBIRD_UP_RIGHT,const int HUMMINGBIRD_DOWN_LEFT,const int HUMMINGBIRD_DOWN_RIGHT,Clock& hummingbirdMovementClock);

void hummingbirdEatHoneycomb(float hummingbird_x, float hummingbird_y, const int maxWorkerbeehoneycombs, float workerbeehoneycomb_x[], float workerbeehoneycomb_y[], bool workerbeehoneycomb_exists[],const int maxRedHoneycombs, float redHoneycomb_x[], float redHoneycomb_y[], bool redHoneycomb_exists[],int& score);

void hummingbirdHitByBullet(float bullet_x, float bullet_y, bool& bullet_exists, float hummingbird_x, float hummingbird_y, bool& hummingbird_exists, bool& hummingbird_sick, int& hummingbird_health);

void initializeFlowers(bool flowersInLastTier[], Sprite flowerSprites[], int gameRows, Texture& flowerTexture);

void placeFlowerAtTile(bool flowersInLastTier[], Sprite flowerSprites[], int tileIndex);

bool findFreeTileAndPlaceFlower(bool flowersInLastTier[], Sprite flowerSprites[], float bee_x, int gameRows);

void handleBeeFlowerPlacement(bool& firstBeeFlowerDone, bool flowersInLastTier[], Sprite flowerSprites[], int gameRows, float& bee_x, float& bee_y, bool& bee_exists, bool& bee_movingRight);

void drawFlowers(RenderWindow& window, const bool flowersInLastTier[], const Sprite flowerSprites[], int gameRows);

void drawScore(RenderWindow& window, Font& font, int score);

int hummingBirdpoints(bool isRed,float y);

void bonuscan(int score,int& nextBonusScore,int& canCount);

void loadHighScores(const string& filename, string names[], int scores[],const int MAX_HIGH_SCORES);

void saveHighScores(const string& filename, const string names[], const int scores[],const int MAX_HIGH_SCORES);

bool updateHighScores(int playerScore, string& playerName, string names[], int scores[],const int MAX_HIGH_SCORES);

void displayHighScores(RenderWindow& window, Font& font, const string names[], const int scores[],const int MAX_HIGH_SCORES);

void promptPlayerName(RenderWindow& window, Font& font, string& playerName);

bool isColliding(int obj1_x, int obj1_y, int obj1_w, int obj1_h,int obj2_x, int obj2_y, int obj2_w, int obj2_h);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                                                                         ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	srand(time(0));

	//Declaring RenderWindow.
	RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

	//Used to position your window on every launch. Use according to your needs.
	window.setPosition(Vector2i(500, 200));

	//Initializing Background Music.
	Music bgMusic;
	if(!bgMusic.openFromFile("Music/Music3.ogg")){
    cout << "Error: Could not load music file!" << endl;
	}
	bgMusic.setVolume(50);
	bgMusic.setLoop(true);
	bgMusic.play();

	//Initializing Player and Player Sprites.
	float player_x = (gameRows / 2) * boxPixelsX;
	float player_y = (gameColumns - 4) * boxPixelsY;

	Texture playerTexture;
	Sprite playerSprite;
	playerTexture.loadFromFile("Textures/spray.png");
	playerSprite.setTexture(playerTexture);
	//Initializing Bullet and Bullet Sprites
	//Data for bullet / Spray pellet

	float bullet_x = player_x;
	float bullet_y = player_y;
	bool bullet_exists = false;

	Clock bulletClock;
	Texture bulletTexture;
	Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setScale(3, 3);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	//The ground on which player moves

	RectangleShape groundRectangle(Vector2f(960, 64));
	groundRectangle.setPosition(0, (gameColumns - 2) * boxPixelsY);
	groundRectangle.setFillColor(Color::Green);
	//////////////////////////////////
	//Player Movement intializations//
	//////////////////////////////////
	Keyboard key;
    Clock delayTime;
    Font font;
	font.loadFromFile("Fonts/dpcomic.ttf");
	////////////
	//MENU BAR//
	////////////
	Texture menuTexture;
	Sprite menuSprite;
	menuTexture.loadFromFile("Textures/background.png");
    menuSprite.setTexture(menuTexture);
	menuSprite.setScale(1.8f,1.9f);


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                             SPRAY CAN                                   //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

int canCount = 3;              //Start with 3 cans
int nextBonusScore = 20000; //Initial threshold for bonus can
int spraysUsedInCurrentCan = 0; //0 to 56 for the current can
const int SPRAYS_PER_CAN = 56;
const int SPRAYS_PER_LEVEL = 8;


///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////

	
/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                           WORKER BEES                                   //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


//  ===================== Workerbee Initializations =====================
	const int maxWorkerBee=20;
	Clock workerBeeStopClocks[maxWorkerBee];//Clock to track how long a bee has been stopped
	Clock workerBeespawnClock;//for bees
	Clock workerBeeClocks[maxWorkerBee];
	int workerBeenextSpawnTime = 0;//Next spawn time in milliseconds
	int totalworkerBeesSpawned = 0;
	int workerBeestopCount[maxWorkerBee] = {0};//How many times each bee has stopped so far
	int workerBeemaxStops[maxWorkerBee] = {0};//Maximum number of stops for each bee (2 or 3)
	float workerBee_x[maxWorkerBee] = {0};
	float workerBee_y[maxWorkerBee] = {0};
	float workerBeeSpeeds[maxWorkerBee] = {0}; //Speed in pixels per second
	float workerBeestopTime[maxWorkerBee] = {0.0f};//Duration for  which a bee stops
	bool workerBeemovingRight[maxWorkerBee] = {true};
	bool Workerbee_exists[maxWorkerBee]={false};
	bool workerBeestopped[maxWorkerBee] = {false};//Tracks if a bee is currently stopped

//  ===================== Workerbee Sprites =====================
	Texture workerBeeTexture;
	Sprite workerBeeSprite[maxWorkerBee];
	workerBeeTexture.loadFromFile("Textures/Regular_bee.png");
	for(int i = 0; i < maxWorkerBee; i++)
    {workerBeeSprite[i].setTexture(workerBeeTexture);}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                          WORKER BEE HONEY COMBS                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//  ===================== Workerbee Honeycomb Initializations =====================
const int maxWorkerbeehoneycombs = 20;
float workerbeehoneycomb_x[maxWorkerbeehoneycombs] = {0};
float workerbeehoneycomb_y[maxWorkerbeehoneycombs] = {0};
bool workerbeehoneycomb_exists[maxWorkerbeehoneycombs] = {false};
Sprite workerbeehoneycombSprites[maxWorkerbeehoneycombs];



//  ===================== Workerbee Honeycomb Sprites =====================
    Texture workerbeehoneycombTexture;
    workerbeehoneycombTexture.loadFromFile("Textures/honeycomb.png");
    //Initialize honeycomb sprites
    for(int i = 0; i < maxWorkerbeehoneycombs; i++)
    {workerbeehoneycombSprites[i].setTexture(workerbeehoneycombTexture);}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                           KILLER BEES                                   //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


//  ===================== Killerbees Initializations =====================
const int maxKillerBees = 10; //Adjust as needed
float killerBee_x[maxKillerBees] = {0};
float killerBee_y[maxKillerBees] = {0};
bool killerBee_exists[maxKillerBees] = {false};
bool killerBee_movingRight[maxKillerBees] = {true};
Clock killerBeeClocks[maxKillerBees];
float killerBeeSpeeds[maxKillerBees] = {0}; //Speed in pixels per second
Clock killerBeeSpawnClock;           //forkiller bees
int nextKillerBeeSpawnTime = 0;      //Next spawn time in milliseconds
int totalKillerBeesSpawned = 0;      //Total killer bees spawned
//  ===================== Killerrbee Sprites =====================
    Texture killerBeeTexture;
	Sprite killerBeeSprites[maxKillerBees];
    killerBeeTexture.loadFromFile("Textures/Fast_bee.png");
	for(int i = 0; i < maxKillerBees; i++){
        killerBeeSprites[i].setTexture(killerBeeTexture);
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                          KILLER BEE HONEY COMBS                         //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//  ===================== Red Honeycombs Initializations =====================
const int maxRedHoneycombs = 20; //Adjust as needed
float redHoneycomb_x[maxRedHoneycombs] = {0};
float redHoneycomb_y[maxRedHoneycombs] = {0};
bool redHoneycomb_exists[maxRedHoneycombs] = {false};


//  ===================== Red Honeycomb Sprites =====================

    Texture redHoneycombTexture;
	Sprite red_honeycombSprites[maxRedHoneycombs];
	redHoneycombTexture.loadFromFile("Textures/honeycomb_red.png");
	for(int i = 0; i < maxRedHoneycombs; i++){
    	red_honeycombSprites[i].setTexture(redHoneycombTexture);
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                           HUMMING BIRD                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//  ===================== Humming bird Initializations =====================
float hummingbird_x, hummingbird_y;
bool hummingbird_exists;
bool hummingbird_sick;
int hummingbird_health; //e.g., 3 hits until sick
bool hummingbird_flapOpen; //to track the flap state of the wings
bool hummingbird_paused; //hummingbird might stop temporarily before changing direction
//Assigning values to every direction for their movement
const int HUMMINGBIRD_LEFT = 0;
const int HUMMINGBIRD_RIGHT = 1;
const int HUMMINGBIRD_UP = 2;
const int HUMMINGBIRD_DOWN = 3;
const int HUMMINGBIRD_UP_LEFT = 4;
const int HUMMINGBIRD_UP_RIGHT = 5;
const int HUMMINGBIRD_DOWN_LEFT = 6;
const int HUMMINGBIRD_DOWN_RIGHT = 7;
int hummingbird_direction;//Direction of humming bord
Clock hummingbirdDirectionClock;
Clock hummingbirdAnimationClock;
Clock hummingbirdPauseClock;
Clock hummingbirdRespawnClock;
float hummingbirdSpeed;
float hummingbird_pauseDuration;
int hummingbird_hitsToSick = 3;//No of hits that a humming bird gets sick
Texture hummingbirdTexture;
Sprite hummingbirdSprite;
Clock hummingbirdMovementClock;
initializeHummingbird(hummingbird_x, hummingbird_y,hummingbird_exists, hummingbird_sick, hummingbird_health, hummingbird_flapOpen, hummingbird_paused,hummingbird_direction, hummingbirdSpeed,hummingbirdDirectionClock, hummingbirdAnimationClock, hummingbirdPauseClock, hummingbirdRespawnClock,hummingbirdTexture, hummingbirdSprite,HUMMINGBIRD_RIGHT);

///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                              FLOWER                                     //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////


//  ===================== Flower Initializations =====================

bool flowersInLastTier[gameRows] = {false}; //Track which tiles in the last tier have flowers
bool firstBeeFlowerDone = false;            //Track if the first bee placed two flowers
Texture flowerTexture;
Sprite flowerSprites[gameRows];            //One sprite per possible tile in last tier
flowerTexture.loadFromFile("Textures/flowers.png");
for(int i=0; i<gameRows; i++){
    flowerSprites[i].setTexture(flowerTexture);
    //Position will be set when a flower is placed.
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                         SCORING MECHANISM                               //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////
    int score = 0;
    const int MAX_HIGH_SCORES = 10;
    std::string highScoreNames[MAX_HIGH_SCORES];
    int highScores[MAX_HIGH_SCORES];
    loadHighScores("highscores.txt", highScoreNames, highScores, MAX_HIGH_SCORES);//LOADING HIGH SCORES FROM FILE
    std::string playerName = "";
    bool startGame = false;
    Menu(window, bgMusic, startGame, font, menuSprite, highScoreNames, highScores, MAX_HIGH_SCORES, playerName);
    if(!startGame)
    {return 0;} //Exit if the game is not started

///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                 ///
///////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
/////                         GAME SCREEN                                     ///
/////////////////////////////////////////////////////////////////////////////////

    Texture gameTexture;
	Sprite gameSprite;
	gameTexture.loadFromFile("Textures/level1.png");
    gameSprite.setTexture(gameTexture);
    gameSprite.setScale(1.2,1.2);

///////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                ///
///////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////
	//GAME LOOP//
	/////////////
	while(window.isOpen()){

		Event e;
		while(window.pollEvent(e)){
			if (e.type == Event::Closed){
				return 0;
			}
		}
//Handle ESC key to end the game
            if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape){
                //Update high scores
                if (updateHighScores(score, playerName, highScoreNames, highScores, MAX_HIGH_SCORES)){
                    //Save updated high scores to file
                    saveHighScores("highscores.txt", highScoreNames, highScores, MAX_HIGH_SCORES);
                }
                //Return to menu
                Menu(window, bgMusic, startGame, font, menuSprite, highScoreNames, highScores, MAX_HIGH_SCORES, playerName);
                if (!startGame){
                    return 0; //Exit if the game is not started
                }
            }

if(key.isKeyPressed(Keyboard::Space)){
    if(!bullet_exists){
        bullet_exists = true;
        bullet_x = player_x + (boxPixelsX / 2) - (96.0f / 2);
        bullet_y = player_y;
        bulletClock.restart();

        //After firing a bullet, increment sprays:
        if(canCount > 0){
            spraysUsedInCurrentCan++;
            if(spraysUsedInCurrentCan >= SPRAYS_PER_CAN){
                canCount--;
                if(canCount > 0){
                    spraysUsedInCurrentCan = 0; //New can starts full
                } else {
                    //No more cans left, last can is empty now
                    spraysUsedInCurrentCan = SPRAYS_PER_CAN; //remain at 56 to indicate empty
                }
            }
        }
    }
}
		///////////////////////////////////////////////////////////////
		//                                                           //
		//Call Your Functions Here. Some have been written for you.  //
		//Be vary of the order you call them, SFML draws in order.   //
		//                                                           //
		///////////////////////////////////////////////////////////////
        window.draw(gameSprite);
		bonuscan(score, nextBonusScore, canCount);
		playerMovement(player_x, player_y, delayTime, key,flowersInLastTier);
		drawworkerBee(window,workerBeeSprite,maxWorkerBee,Workerbee_exists);
		drawKillerBee(window,maxKillerBees,killerBee_exists,killerBeeSprites);
		moveWorkerBee(window,workerBeeSprite,maxWorkerBee,Workerbee_exists,workerBee_x,workerBee_y,workerBeemovingRight,workerBeeClocks,workerBeeSpeeds,workerBeespawnClock,workerBeenextSpawnTime,totalworkerBeesSpawned,workerBeestopped,workerBeestopTime,workerBeeStopClocks,workerBeestopCount,workerBeemaxStops,firstBeeFlowerDone,flowersInLastTier,flowerSprites);
		moveKillerBee(maxKillerBees,killerBee_x,killerBee_y,killerBee_exists,killerBee_movingRight,killerBeeClocks,killerBeeSpeeds,killerBeeSpawnClock,nextKillerBeeSpawnTime,totalKillerBeesSpawned,killerBeeSprites,firstBeeFlowerDone,flowersInLastTier,flowerSprites);
		collisionDetection(bullet_x,bullet_y, bullet_exists,maxWorkerBee,Workerbee_exists,workerBee_x,workerBee_y,workerbeehoneycombSprites,maxWorkerbeehoneycombs,workerbeehoneycomb_x,workerbeehoneycomb_y,workerbeehoneycomb_exists,workerBeemovingRight,workerBeeSprite,maxKillerBees,maxRedHoneycombs,redHoneycomb_x,redHoneycomb_y,redHoneycomb_exists,red_honeycombSprites,killerBee_x,killerBee_y,killerBee_exists,score);
		drawworkerbeehoneycomb(window,maxWorkerbeehoneycombs,workerbeehoneycomb_exists,workerbeehoneycombSprites);
		drawRedHoneycombs(window,maxRedHoneycombs,redHoneycomb_x,redHoneycomb_y,redHoneycomb_exists,red_honeycombSprites);
		moveHummingbird(hummingbird_x, hummingbird_y,hummingbird_exists, hummingbird_sick,hummingbird_health,hummingbird_paused, hummingbird_pauseDuration,hummingbird_direction, hummingbirdSpeed,hummingbirdDirectionClock, hummingbirdAnimationClock, hummingbirdPauseClock, hummingbirdRespawnClock,hummingbird_flapOpen, hummingbirdSprite,HUMMINGBIRD_LEFT,HUMMINGBIRD_RIGHT,HUMMINGBIRD_UP,HUMMINGBIRD_DOWN,HUMMINGBIRD_UP_LEFT,HUMMINGBIRD_UP_RIGHT,HUMMINGBIRD_DOWN_LEFT,HUMMINGBIRD_DOWN_RIGHT,hummingbirdMovementClock);
		hummingbirdEatHoneycomb(hummingbird_x, hummingbird_y,maxWorkerbeehoneycombs, workerbeehoneycomb_x, workerbeehoneycomb_y, workerbeehoneycomb_exists,maxRedHoneycombs, redHoneycomb_x, redHoneycomb_y, redHoneycomb_exists,score);
		hummingbirdHitByBullet(bullet_x, bullet_y, bullet_exists,hummingbird_x, hummingbird_y,hummingbird_exists, hummingbird_sick, hummingbird_health);
		drawHummingbird(window, hummingbird_exists, hummingbirdSprite);


		if(bullet_exists == true)
		{
			moveBullet(bullet_y, bullet_exists, bulletClock);
			drawBullet(window, bullet_x, bullet_y, bulletSprite);
		}
		else
		{
			bullet_x = player_x+32;
			bullet_y = player_y;
		}
		window.draw(groundRectangle);
        drawScore(window, font, score);
		drawPlayer(window,player_x,player_y,playerSprite,canCount,spraysUsedInCurrentCan,SPRAYS_PER_CAN,SPRAYS_PER_LEVEL,font);
		drawFlowers(window,flowersInLastTier,flowerSprites,gameRows);
		window.display();
		window.clear();
	}
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
//Write your functions definitions here. Some have been written for you.  //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

void Menu(RenderWindow& window, Music& bgMusic, bool& startGame, Font& font, Sprite& menuSprite, 
              std::string highScoreNames[], int highScores[], const int MAX_HIGH_SCORES,
              std::string& playerName){
    const int optionsCount = 5; //Level 1, Level 2, Level 3, High Scores, Quit
    const string optionTexts[optionsCount] = { "Level 1", "Level 2", "Level 3", "High Scores", "Quit" };
    Text options[optionsCount];

    for(int i = 0; i < optionsCount; i++){
        options[i].setFont(font);
        options[i].setString(optionTexts[i]);
        options[i].setCharacterSize(40);
        options[i].setFillColor(Color::White);
        options[i].setOutlineColor(Color::Black);
        options[i].setOutlineThickness(2);
        options[i].setPosition(400, 150 + i * 100);
    }

    //Title text
    Text title;
    title.setFont(font);
    title.setString("BUZZ BOMBERS");
    title.setCharacterSize(100);
    title.setFillColor(Color::Yellow);
    title.setOutlineColor(Color::Black);
    title.setOutlineThickness(2);
    title.setPosition(200, 30);

    //Highlight the first option
    int selectedOption = 0;
    options[selectedOption].setFillColor(Color::Yellow);

    //Menu loop
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
                return;
            }
//Handle keyboard input
if(event.type == Event::KeyPressed){
if(event.key.code == Keyboard::Up){
    options[selectedOption].setFillColor(Color::White); //Reset previous selection
    selectedOption = (selectedOption - 1 + optionsCount) % optionsCount; //Move selection up
    options[selectedOption].setFillColor(Color::Yellow); //Highlight new selection
}
else if(event.key.code == Keyboard::Down){
    options[selectedOption].setFillColor(Color::White);
    selectedOption = (selectedOption + 1) % optionsCount;
    options[selectedOption].setFillColor(Color::Yellow);
}
else if(event.key.code == Keyboard::Enter){
    if(selectedOption == 4){ //Quit
        window.close();
        return;
    }
    else if(selectedOption == 3){ //High Scores
        //Display High Scores
        window.clear();
        displayHighScores(window, font, highScoreNames, highScores, MAX_HIGH_SCORES);
        window.display();
//Wait until the user presses Escape to return to the menu
bool backToMenu = false;
while(!backToMenu && window.isOpen()){
    Event hsEvent;
    while(window.pollEvent(hsEvent)){
        if(hsEvent.type == Event::Closed){
            window.close();
            return;
        }
        if(hsEvent.type == Event::KeyPressed && hsEvent.key.code == Keyboard::Escape){
            backToMenu = true;
        }
    }
}

    //Reset the window after displaying high scores
    window.clear();
    window.draw(menuSprite);
    window.draw(title);
    for(int i = 0; i < optionsCount; i++){
        window.draw(options[i]);
    }
    window.display();
    }
    else { //Level 1, Level 2, Level 3
        //Prompt forplayer name before starting the level
        promptPlayerName(window, font, playerName);
        if(playerName.empty()){
            //if no name entered, assign a default name
            playerName = "unnamed_";
        }
        //Start the game
        startGame = true;
        return;
           }
        }
    }
}
//Draw menu
    window.clear();
    window.draw(menuSprite);
    window.draw(title);
    for(int i = 0; i < optionsCount; i++){
        window.draw(options[i]);
    }
    window.display();
    }
}

void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite,int& canCount,int& spraysUsedInCurrentCan,const int SPRAYS_PER_CAN,const int SPRAYS_PER_LEVEL,Font font){
//Draw the player sprite first
playerSprite.setPosition(player_x, player_y);
window.draw(playerSprite);
int spareCans = canCount - 1; //since one is in use
    for(int i = 0; i < spareCans; i++){
int offsetX = 10 + 2*i * 40; //spacing between cans
int offsetY = resolutionY - 64; //just above the bottom bar
//Draw the sprite for the spare can
Sprite spareSprite = playerSprite;
spareSprite.setPosition(offsetX, offsetY);
window.draw(spareSprite);
Text sprayCountText;
sprayCountText.setFont(font); //Set the font
sprayCountText.setCharacterSize(24); //Set character size
sprayCountText.setFillColor(Color::Yellow); //Set text color
 //Calculate sprays left in the current can
int spraysLeft = SPRAYS_PER_CAN - spraysUsedInCurrentCan;
if(canCount <= 0)
spraysLeft = 0;
//Set the string to display the number of sprays left
sprayCountText.setString("Sprays Left: " + to_string(spraysLeft));
sprayCountText.setPosition(player_x, player_y - 30); //30 pixels above the spray can
window.draw(sprayCountText);
}
}
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock){
	if(bulletClock.getElapsedTime().asMilliseconds() < 20)
		return;
	bulletClock.restart();
	bullet_y -= 10;
	if(bullet_y < -32)
		bullet_exists = false;
}
void drawBullet(sf::RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite){
	bulletSprite.setPosition(bullet_x+32, bullet_y);
	window.draw(bulletSprite);
}

void playerMovement(float& player_x, float& player_y, Clock& delayTime, Keyboard& key,bool flowersInLastTier[]){
    const double minDelaytime = 200;
    if(delayTime.getElapsedTime().asMilliseconds() > minDelaytime){
        float next_x = player_x; 
if(key.isKeyPressed(Keyboard::Right)){
    if(player_x < resolutionX - 64){
        next_x = player_x + 32.0f;
        int tile = (int)(next_x / 32);
        //Check if the tile is occupied by a flower before moving horizontally
        if(!flowersInLastTier[tile]){
            player_x = next_x;
            delayTime.restart();
        }
        //else blocked by flower, do nothing
    }
}
if(key.isKeyPressed(Keyboard::Left)){
    if(player_x > 0){
        next_x = player_x - 32.0f;
        int tile = (int)(next_x / 32);

        //Check if the tile is occupied by a flower before moving horizontally
        if(!flowersInLastTier[tile]){
            player_x = next_x;
            delayTime.restart();
        }
        //else blocked by flower, do nothing
            }
        }
    }
}
void drawworkerBee(RenderWindow& window,Sprite workerBeeSprite[],const int maxWorkerBee,bool Workerbee_exists[]){
    for(int i = 0; i < maxWorkerBee; i++){
        if(Workerbee_exists[i]){
            window.draw(workerBeeSprite[i]);
        }
    }
}
void moveWorkerBee(RenderWindow& window,Sprite workerBeeSprite[],const int maxWorkerBee,bool Workerbee_exists[],float workerBee_x[],float workerBee_y[],bool workerBeemovingRight[],Clock workerBeeClocks[],float workerBeeSpeeds[],Clock& workerBeespawnClock,int& workerBeenextSpawnTime,int& totalworkerBeesSpawned,bool workerBeestopped[],float workerBeestopTime[],Clock workerBeeStopClocks[],int workerBeestopCount[],int workerBeemaxStops[],bool& firstBeeFlowerDone,bool flowersInLastTier[],Sprite flowerSprites[]){
    //Handle spawning of a new honeybee only if totalBeesSpawned < maxWorkerBee
    if(workerBeespawnClock.getElapsedTime().asMilliseconds() > workerBeenextSpawnTime && totalworkerBeesSpawned < maxWorkerBee){
        //Find a free bee slot
        for(int i = 0; i < maxWorkerBee; i++){
    if(!Workerbee_exists[i]){
        Workerbee_exists[i] = true;
        workerBee_x[i] = rand() % (resolutionX - 50);//Assuming bee sprite width is 50
        workerBee_y[i] = 0;
        workerBeemovingRight[i] = rand() % 2;//Random direction: 0 = left, 1 = right
        workerBeeClocks[i].restart();
        workerBeeSpeeds[i] = 200.0f + (rand() % 51);//Speed between 350 to 400 pixels/sec
        //Set initial direction
        if(workerBeemovingRight[i]){
            workerBeeSprite[i].setScale(1, 1); //Facing right
        } else {
            workerBeeSprite[i].setScale(-1, 1); //Facing left (flipped)
        }

        //Initialize stop logic
        workerBeestopped[i] = false;
        workerBeestopCount[i] = 0;
        workerBeemaxStops[i] = 2 + (rand() % 2); //Bee will stop 2 or 3 times in total

        totalworkerBeesSpawned++; //Increment total bees spawned
        break; //Spawn only one bee at a time
    }
}
        //Reset spawn clock and set next spawn time
        workerBeenextSpawnTime = rand() % 5000 + 1000; //Next spawn between 1-6 seconds
        workerBeespawnClock.restart();
    }

    //Update positions and states of all active honeybees
    for(int i = 0; i < maxWorkerBee; i++){
        if(Workerbee_exists[i]){
            float deltaTime = workerBeeClocks[i].restart().asSeconds();

            //Check if bee is currently stopped
    if(workerBeestopped[i]){
        //if bee is stopped, check if stop time has elapsed
        if(workerBeeStopClocks[i].getElapsedTime().asSeconds() > workerBeestopTime[i]){
            //Stopping duration over, resume movement
            workerBeestopped[i] = false;
        } else {
            //Bee remains stopped, no horizontal movement
            //Update sprite position in case of vertical changes
            workerBeeSprite[i].setPosition(workerBee_x[i], workerBee_y[i]);
            continue; //Skip the rest of the logic for this bee
        }
    } else {
        //Bee is not stopped, consider initiating a stop if it hasn't reached max stops
        if(workerBeestopCount[i] < workerBeemaxStops[i]){
            //Low probability check to trigger a stop (rare event)
            if(rand() % 30000 == 0){//When bee is to be stopped probability
            workerBeestopped[i] = true;
            workerBeeStopClocks[i].restart();
            workerBeestopTime[i] = 0.5f + static_cast<float>(rand() % 1501) / 1000.0f; //0.5 to 2.0 seconds
            workerBeestopCount[i]++; //Increment stop count as we've initiated a stop
            }
        }
    }

            //if not stopped, proceed with movement
    if(!workerBeestopped[i]){
    if(workerBeemovingRight[i]){
        workerBee_x[i] += workerBeeSpeeds[i] * deltaTime;
    } else {
        workerBee_x[i] -= workerBeeSpeeds[i] * deltaTime;
    }
}

    //Check for collision with screen boundaries
    if(workerBeemovingRight[i] && (workerBee_x[i] + 50 >= resolutionX)){ //Right Boundary
        if(workerBee_y[i] < (gameColumns - 3) * boxPixelsY){
        workerBee_x[i] = resolutionX - 50;
        workerBeemovingRight[i] = false;
        workerBee_y[i] += boxPixelsY; //Move down to next tier
        workerBeeSprite[i].setScale(-1, 1); //Face left (flipped)
		if(workerBee_y[i] == 544){
    handleBeeFlowerPlacement(firstBeeFlowerDone, flowersInLastTier, flowerSprites, gameRows,workerBee_x[i], workerBee_y[i],Workerbee_exists[i], workerBeemovingRight[i]);}
        //if the bee reversed direction to exit, check ifit left the screen:
        if(workerBee_x[i] < -50 || workerBee_x[i] > resolutionX){
            Workerbee_exists[i] = false;
        }
    }
}
    else if(!workerBeemovingRight[i] && (workerBee_x[i] <= 32)){ //Left Boundary with 32-pixel buffer
    if(workerBee_y[i] < (gameColumns - 3) * boxPixelsY){
        workerBee_x[i] = 64; //Prevent moving beyond 64 pixels from the left
        workerBeemovingRight[i] = true;
        workerBee_y[i] += boxPixelsY; //Move down to next tier
        workerBeeSprite[i].setScale(1, 1); //Face right
	if(workerBee_y[i] == 544)
    {handleBeeFlowerPlacement(firstBeeFlowerDone, flowersInLastTier, flowerSprites, gameRows,workerBee_x[i], workerBee_y[i],Workerbee_exists[i], workerBeemovingRight[i]);}
    //if the bee reversed direction to exit, check if it left the screen:
    if(workerBee_x[i] < -50 || workerBee_x[i] > resolutionX){
            Workerbee_exists[i] = false;}
        } 
    }
        //Update sprite position
        workerBeeSprite[i].setPosition(workerBee_x[i], workerBee_y[i]);
    //Check if bee has reached the ground or bottom of the screen
    if(workerBee_y[i] > (gameColumns - 2) * boxPixelsY){
        Workerbee_exists[i] = false; //Remove bee from the game
            }
        }
    }
}
bool isColliding(int obj1_x, int obj1_y, int obj1_w, int obj1_h,int obj2_x, int obj2_y, int obj2_w, int obj2_h)
{ return (obj1_x < obj2_x + obj2_w &&obj1_x + obj1_w > obj2_x &&obj1_y < obj2_y + obj2_h &&obj1_y + obj1_h > obj2_y);}
void collisionDetection(float& bullet_x, float& bullet_y, bool& bullet_exists,const int maxWorkerBee,bool Workerbee_exists[],float workerBee_x[],float workerBee_y[],Sprite workerbeehoneycombSprites[],const int maxWorkerbeehoneycombs,float workerbeehoneycomb_x[],float workerbeehoneycomb_y[],bool workerbeehoneycomb_exists[],bool workerBeemovingRight[],Sprite workerBeeSprite[],const int maxKillerBees,const int maxRedHoneycombs,float redHoneycomb_x[],float redHoneycomb_y[],bool redHoneycomb_exists[],Sprite red_honeycombSprites[],float killerBee_x[],float killerBee_y[],bool killerBee_exists[],int& score){
    //Define sizes
    const float bee_width = 46;
    const float bee_height = 22;
    const float bullet_width = 16;    
    const float bullet_height = 16; 
    const float honeycomb_width = 64;
    const float honeycomb_height = 64;

    //1. Check collision with WORKER BEES
    for(int i = 0; i < maxWorkerBee; i++){
        if(Workerbee_exists[i] && bullet_exists){
        if(isColliding(bullet_x, bullet_y, bullet_width, bullet_height,workerBee_x[i], workerBee_y[i], bee_width, bee_height)){
		score+=100;
		Workerbee_exists[i] = false;  //Remove bee
        bullet_exists = false;  //Remove bullet
         //Find a free normal honeycomb slot
        for(int j = 0; j < maxWorkerbeehoneycombs; j++){
            if(!workerbeehoneycomb_exists[j]){
                workerbeehoneycomb_exists[j] = true;
                workerbeehoneycomb_x[j] = workerBee_x[i];
                workerbeehoneycomb_y[j] = workerBee_y[i];
                workerbeehoneycombSprites[j].setPosition(workerbeehoneycomb_x[j], workerbeehoneycomb_y[j]);
                break; //Spawn only one honeycomb
            }
        }
    break; //Exit loop after handling collision
            }
        }
    }

//2. Check collision with WORKER BEES HONEYCOMBS
    for(int j = 0; j < maxWorkerbeehoneycombs; j++){
        if(workerbeehoneycomb_exists[j] && bullet_exists){
            if(isColliding(bullet_x, bullet_y, bullet_width, bullet_height,workerbeehoneycomb_x[j], workerbeehoneycomb_y[j], honeycomb_width, honeycomb_height)){
    //Bullet hit a normal honeycomb
        workerbeehoneycomb_exists[j] = false; //Remove honeycomb
        bullet_exists = false;       //Remove bullet
            break; //Exit loop after handling collision
        }
    }
}
 // 3. Check collision with KILLER BEES
    for(int i = 0; i < maxKillerBees; i++){
        if(killerBee_exists[i] && bullet_exists){
            if(isColliding(bullet_x, bullet_y, bullet_width, bullet_height,
	            killerBee_x[i], killerBee_y[i], bee_width, bee_height)){
	//Bullet hit a killer bee
	//Add score of 1000 points
	score+=1000;
	killerBee_exists[i] = false; //Remove killer bee
	bullet_exists = false;       //Remove bullet
	//Spawn red honeycomb at collision position
	//Find a free red honeycomb slot
	for(int k = 0; k < maxRedHoneycombs; k++){
	    if(!redHoneycomb_exists[k]){
	    redHoneycomb_exists[k] = true;
	    redHoneycomb_x[k] = killerBee_x[i];
	    redHoneycomb_y[k] = killerBee_y[i];
	    red_honeycombSprites[k].setPosition(redHoneycomb_x[k], redHoneycomb_y[k]);
	    break; //Spawn only one red honeycomb
	    }
	}
      break; //Exit after handling collision
	    }
    }
}

//4. Check collision with RED HONEYCOMBS
    for(int m = 0; m < maxRedHoneycombs; m++){
        if(redHoneycomb_exists[m] && bullet_exists){
        if(isColliding(bullet_x, bullet_y, bullet_width, bullet_height,redHoneycomb_x[m], redHoneycomb_y[m], honeycomb_width, honeycomb_height)){
        //Bullet hit a red honeycomb
        redHoneycomb_exists[m] = false; //Remove red honeycomb
        bullet_exists = false;          //Remove bullet
        break; //Exit loop after handling collision
        }
    }
}
//5. Check collision between yellowhoneycomb and bee
	for(int j = 0; j < maxWorkerbeehoneycombs; j++){
if(workerbeehoneycomb_exists[j] || redHoneycomb_exists[j]){
    //Iterate through all bees to check collision with this wrokerbeehoneycomb and redhoney comb
    for(int i = 0; i < maxWorkerBee; i++){
        if(Workerbee_exists[i]){
        if(isColliding(workerbeehoneycomb_x[j], workerbeehoneycomb_y[j], honeycomb_width, honeycomb_height,workerBee_x[i], workerBee_y[i], bee_width, bee_height) || isColliding(redHoneycomb_x[j], redHoneycomb_y[j], honeycomb_width, honeycomb_height,workerBee_x[i], workerBee_y[i], bee_width, bee_height))
        {
        //Collision detected between honeycomb and bee
        //Reverse bee's direction
        workerBeemovingRight[i] = !workerBeemovingRight[i];
        if(workerBeemovingRight[i]){
            workerBeeSprite[i].setScale(1, 1); //Face right
        }
        else {
            workerBeeSprite[i].setScale(-1, 1); //Face left
        }
        //Move bee down to the next row
        workerBee_y[i] += boxPixelsY;
        //Update bee's sprite position
        workerBeeSprite[i].setPosition(workerBee_x [i], workerBee_y[i]);
        //Check if bee has reached the ground or bottom of the screen
        if(workerBee_y[i] > (gameColumns - 2) * boxPixelsY){
            Workerbee_exists[i] = false; //Remove bee from the game
                        }
                    }
                }
            }
        }
    }
}
void drawworkerbeehoneycomb(RenderWindow& window,const int maxWorkerbeehoneycombs,bool workerbeehoneycomb_exists[],Sprite workerbeehoneycombSprites[]){
for(int i = 0; i < maxWorkerbeehoneycombs; i++){
    	if(workerbeehoneycomb_exists[i]){
        	window.draw(workerbeehoneycombSprites[i]);
    	}
	}
}
void drawKillerBee(RenderWindow& window,const int maxKillerBees,bool killerBee_exists[],Sprite killerBeeSprites[]){
    for(int i = 0; i < maxKillerBees; i++){
        if(killerBee_exists[i]){
            window.draw(killerBeeSprites[i]);
        }
    }
}
void moveKillerBee(const int maxKillerBees,float killerBee_x[],float killerBee_y[],bool killerBee_exists[],bool killerBee_movingRight[],Clock killerBeeClocks[],float killerBeeSpeeds[],Clock& killerBeeSpawnClock,int& nextKillerBeeSpawnTime,int& totalKillerBeesSpawned,Sprite killerBeeSprites[],bool& firstBeeFlowerDone,bool flowersInLastTier[],Sprite flowerSprites[]){
    //Handle spawning of a new killer bee only if totalKillerBeesSpawned < MAX_KILLER_BEES
if(killerBeeSpawnClock.getElapsedTime().asMilliseconds() > nextKillerBeeSpawnTime && totalKillerBeesSpawned < maxKillerBees){
    //Find a free killer bee slot
    for(int i = 0; i < maxKillerBees; i++){
        if(!killerBee_exists[i]){
        killerBee_exists[i] = true;
        killerBee_x[i] = rand() % (resolutionX - 50); //Assuming killer bee sprite width is 50
        killerBee_y[i] = 0;
        killerBee_movingRight[i] = rand() % 2; //Random direction: 0 = left, 1 = right
        killerBeeClocks[i].restart();
        killerBeeSpeeds[i] = 500.0f + (rand() % 101); //Speed between 450 to 550 pixels/sec
        //Set initial direction
        if(killerBee_movingRight[i])
        {killerBeeSprites[i].setScale(1, 1);} //Facing right
        else
        {killerBeeSprites[i].setScale(-1, 1); }//Facing left (flipped)
        totalKillerBeesSpawned++; //Increment total killer bees spawned
        break; //Spawn only one killer bee at a time
        }
    }
    //Reset spawn clock and set next spawn time
    nextKillerBeeSpawnTime = rand() % 5000 + 1000; //Next spawn between 1-6 seconds
    killerBeeSpawnClock.restart();
}

    //Update positions and states of all active killer bees
    for(int i = 0; i < maxKillerBees; i++){
        if(killerBee_exists[i]){
            float deltaTime = killerBeeClocks[i].restart().asSeconds();

            //Update position based on speed and direction
    if(killerBee_movingRight[i]){
        killerBee_x[i] += killerBeeSpeeds[i] * deltaTime;
    }
    else {
        killerBee_x[i] -= killerBeeSpeeds[i] * deltaTime;
        }

    //Check forcollision with screen boundaries
    if(killerBee_movingRight[i] && (killerBee_x[i] + 50 >= resolutionX)){ //Right Boundary
        if(killerBee_y[i] < (gameColumns - 3) * boxPixelsY){
        killerBee_x[i] = resolutionX - 50;
        killerBee_movingRight[i] = false;
        killerBee_y[i] += boxPixelsY; //Move down to next tier
        killerBeeSprites[i].setScale(-1, 1); //Face left (flipped)
		if(killerBee_y[i] == 544){
    //Now place flowers:
    handleBeeFlowerPlacement(firstBeeFlowerDone, flowersInLastTier, flowerSprites, gameRows,killerBee_x[i], killerBee_y[i], killerBee_exists[i], killerBee_movingRight[i]);
    }
 //if direction reversed, let it move horizontally until out of screen:
    if(killerBee_x[i] < -50 || killerBee_x[i] > resolutionX){
    //Bee out of bounds
    killerBee_exists[i] = false;}
        }
    }
    else if(!killerBee_movingRight[i] && (killerBee_x[i] <= 32)){ //Left Boundary with 32-pixel buffer
        if(killerBee_y[i] < (gameColumns - 3) * boxPixelsY){
            killerBee_x[i] = 64; //Prevent moving beyond 64 pixels from the left
            killerBee_movingRight[i] = true;
            killerBee_y[i] += boxPixelsY; //Move down to next tier
            killerBeeSprites[i].setScale(1, 1); //Face right
		if(killerBee_y[i] == 544){
    //Now place flowers:
    handleBeeFlowerPlacement(firstBeeFlowerDone, flowersInLastTier, flowerSprites, gameRows,killerBee_x[i], killerBee_y[i], killerBee_exists[i], killerBee_movingRight[i]);
    }
        //if the bee is now trying to exit:
        //if direction reversed, let it move horizontally until out of screen:
        if (killerBee_x[i] < -50 || killerBee_x[i] > resolutionX){
            //Bee out of bounds
            killerBee_exists[i] = false;
        }
    }
}
//Update sprite position
    killerBeeSprites[i].setPosition(killerBee_x[i], killerBee_y[i]);
        //Check if killer bee has reached the ground or bottom of the screen
    if(killerBee_y[i] > (gameColumns - 2) * boxPixelsY){
        killerBee_exists[i] = false;} //Remove killer bee from the game  
        }
    }
}
void drawRedHoneycombs(RenderWindow& window,const int maxRedHoneycombs,float redHoneycomb_x[],float redHoneycomb_y[],bool redHoneycomb_exists[],Sprite red_honeycombSprites[]){
    for(int i = 0; i < maxRedHoneycombs; i++){
        if(redHoneycomb_exists[i]){
            window.draw(red_honeycombSprites[i]);
        }
    }
}
void initializeHummingbird(float& hummingbird_x, float& hummingbird_y, bool& hummingbird_exists, bool& hummingbird_sick, int& hummingbird_health, bool& hummingbird_flapOpen, bool& hummingbird_paused,int& hummingbird_direction, float& hummingbirdSpeed,Clock& hummingbirdDirectionClock, Clock& hummingbirdAnimationClock, Clock& hummingbirdPauseClock, Clock& hummingbirdRespawnClock,Texture& hummingbirdTexture, Sprite& hummingbirdSprite,const int HUMMINGBIRD_RIGHT){
hummingbirdTexture.loadFromFile("Textures/bird.png");
hummingbirdSprite.setTexture(hummingbirdTexture);
hummingbirdSprite.setTextureRect(IntRect(0, 0, 32, 32));
//Spawning humming bird in the middle
hummingbird_x = resolutionX / 2.0f;
hummingbird_y = resolutionY / 2.0f;
hummingbird_exists = true;
hummingbird_flapOpen = true;
//spawning humming bird after some seconds
hummingbird_paused = true;
hummingbirdSpeed = 200.0f;
hummingbird_health = 3;
hummingbird_direction = HUMMINGBIRD_RIGHT;
hummingbird_sick = false;
hummingbirdAnimationClock.restart();
hummingbirdDirectionClock.restart();
hummingbirdPauseClock.restart();
hummingbirdRespawnClock.restart();
hummingbirdSprite.setPosition(hummingbird_x, hummingbird_y);
}
void drawHummingbird(RenderWindow& window, bool hummingbird_exists, Sprite& hummingbirdSprite){
    if(hummingbird_exists){
        window.draw(hummingbirdSprite);
    }
}
void moveHummingbird(float& hummingbird_x, float& hummingbird_y, bool& hummingbird_exists, bool& hummingbird_sick, int& hummingbird_health, bool& hummingbird_paused, float& hummingbird_pauseDuration,int& hummingbird_direction, float hummingbirdSpeed,Clock& hummingbirdDirectionClock, Clock& hummingbirdAnimationClock, Clock& hummingbirdPauseClock, Clock& hummingbirdRespawnClock,bool& hummingbird_flapOpen, Sprite& hummingbirdSprite,const int HUMMINGBIRD_LEFT,const int HUMMINGBIRD_RIGHT,const int HUMMINGBIRD_UP,const int HUMMINGBIRD_DOWN,const int HUMMINGBIRD_UP_LEFT ,const int HUMMINGBIRD_UP_RIGHT,const int HUMMINGBIRD_DOWN_LEFT,const int HUMMINGBIRD_DOWN_RIGHT,Clock& hummingbirdMovementClock){
    if(hummingbird_sick && !hummingbird_exists){
     if(hummingbirdRespawnClock.getElapsedTime().asSeconds() > 5.0f){
    hummingbird_exists = true;
    hummingbird_sick = false;
    hummingbird_health = 3;
    hummingbird_x = resolutionX / 2.0f;
    hummingbird_y = resolutionY / 2.0f;
    hummingbird_direction = HUMMINGBIRD_RIGHT;
    hummingbirdSprite.setPosition(hummingbird_x, hummingbird_y);
    hummingbirdRespawnClock.restart();
        }
    return; 
    }
    if(!hummingbird_exists) return;
    float deltaTime = hummingbirdMovementClock.restart().asSeconds();
    //Animation forhumming bird flaps
    if(hummingbirdAnimationClock.getElapsedTime().asMilliseconds() > 200){
        if(hummingbird_flapOpen){
            hummingbirdSprite.setTextureRect(IntRect(32, 0, 32, 32));
        } else {
            hummingbirdSprite.setTextureRect(IntRect(0, 0, 32, 32));
        }
        hummingbird_flapOpen = !hummingbird_flapOpen;
        hummingbirdAnimationClock.restart();
    }

    //Pausing logic
    if(hummingbird_paused){
        if(hummingbirdPauseClock.getElapsedTime().asSeconds() > hummingbird_pauseDuration){
            hummingbird_paused = false;
            hummingbirdDirectionClock.restart();
            //Choose new direction
			//Save the previous direction to avoid repetition
static int lastDirection = -1; //Initialize to an invalid value
static int secondLastDirection = -1;

//Generate multiple candidates and pick one
int candidates[3]; //Pick 3 random candidates
for(int i = 0; i < 3; i++){
    candidates[i] = rand() % 8; //Random direction from 0 to 7
}

//Choose a direction that differs from recent ones
int newDirection = candidates[rand()%4];
for(int i = 1; i < 3; i++){
    if(candidates[i] != lastDirection && candidates[i] != secondLastDirection){
        newDirection = candidates[i];
        break;
    }
}

//Update direction history
secondLastDirection = lastDirection;
lastDirection = hummingbird_direction;

//Assign the new direction
hummingbird_direction = newDirection;

        } else {
            hummingbirdSprite.setPosition(hummingbird_x, hummingbird_y);
            return;
        }
    } else {
        //Create a wider random interval for direction change
float directionChangeInterval = 1.0f + (rand() % 700) / 100.0f; //1.0 to 8.0 seconds

if(hummingbirdDirectionClock.getElapsedTime().asSeconds() > directionChangeInterval){
    hummingbird_paused = true;

    //Randomize pause duration again
    hummingbird_pauseDuration = 0.5f + (rand() % 200) / 100.0f; //0.5 to 2.0 seconds

    hummingbirdPauseClock.restart();
    hummingbirdSprite.setPosition(hummingbird_x, hummingbird_y);
    hummingbirdDirectionClock.restart();
    return;
}

    }

float moveDistance = hummingbirdSpeed * deltaTime;
float diagonalMove = moveDistance / 1.4;
//Before moving the hummingbird, adjust scale based on direction
if(hummingbird_direction == HUMMINGBIRD_LEFT ||hummingbird_direction == HUMMINGBIRD_UP_LEFT ||hummingbird_direction == HUMMINGBIRD_DOWN_LEFT) 
hummingbirdSprite.setScale(-1.0f, 1.0f);
else 
hummingbirdSprite.setScale(1.0f, 1.0f);//for RIGHT, UP_RIGHT, DOWN_RIGHT, UP, DOWN that doesn't involve left movement
    
if(hummingbird_direction == HUMMINGBIRD_LEFT){
    hummingbird_x -= moveDistance;} 

else if(hummingbird_direction == HUMMINGBIRD_RIGHT){
hummingbird_x += moveDistance;}

else if(hummingbird_direction == HUMMINGBIRD_UP){
hummingbird_y -= moveDistance;}

else if(hummingbird_direction == HUMMINGBIRD_DOWN){
hummingbird_y += moveDistance;}

else if(hummingbird_direction == HUMMINGBIRD_UP_LEFT){
hummingbird_x -= diagonalMove;
hummingbird_y -= diagonalMove;} 

else if(hummingbird_direction == HUMMINGBIRD_UP_RIGHT){
hummingbird_x += diagonalMove;
hummingbird_y -= diagonalMove;} 

else if(hummingbird_direction == HUMMINGBIRD_DOWN_LEFT){
hummingbird_x -= diagonalMove;
hummingbird_y += diagonalMove;}

else if(hummingbird_direction == HUMMINGBIRD_DOWN_RIGHT){
hummingbird_x += diagonalMove;
hummingbird_y += diagonalMove;}

//Boundaries
if(hummingbird_x < 32)
hummingbird_x = 32;

if(hummingbird_x > resolutionX - 32)
hummingbird_x = resolutionX - 32;

if(hummingbird_y < 0)
hummingbird_y = 0;

//Prevent the hummingbird from going into the green bar at the bottom
//The green bar starts at resolutionY - 64
//Hummingbird is 32 pixels high, so stop at resolutionY - 64 - 32
if(hummingbird_y > resolutionY - 64 - 32){
    hummingbird_y = resolutionY - 64 - 32;}
    hummingbirdSprite.setPosition(hummingbird_x, hummingbird_y);
}
void hummingbirdEatHoneycomb(float hummingbird_x, float hummingbird_y,const int maxWorkerbeehoneycombs, float workerbeehoneycomb_x[], float workerbeehoneycomb_y[], bool workerbeehoneycomb_exists[],const int maxRedHoneycombs, float redHoneycomb_x[], float redHoneycomb_y[], bool redHoneycomb_exists[],int& score){
    const float bird_width = 64; 
    const float bird_height = 64;
    const float honeycomb_width = 64;
    const float honeycomb_height = 64;
for(int i = 0; i < maxWorkerbeehoneycombs; i++){
    if(workerbeehoneycomb_exists[i]){
    if(isColliding(hummingbird_x, hummingbird_y, bird_width, bird_height,
    workerbeehoneycomb_x[i], workerbeehoneycomb_y[i], honeycomb_width, honeycomb_height)){
    workerbeehoneycomb_exists[i] = false;
	bool red= false;//means it's not red honeycomb
	score+= hummingBirdpoints( red,workerbeehoneycomb_y[i]);
		}
	}
}

for(int j = 0; j < maxRedHoneycombs; j++){
    if(redHoneycomb_exists[j]){
        if(isColliding(hummingbird_x, hummingbird_y, bird_width, bird_height,redHoneycomb_x[j], redHoneycomb_y[j], honeycomb_width, honeycomb_height)){
        redHoneycomb_exists[j] = false;
	bool red= true;//means it's not red honeycomb
	score+= hummingBirdpoints( red,workerbeehoneycomb_y[j]);
            }
        }
    }
}
void hummingbirdHitByBullet(float bullet_x, float bullet_y, bool& bullet_exists,float hummingbird_x, float hummingbird_y, bool& hummingbird_exists, bool& hummingbird_sick, int& hummingbird_health){
    
    const float bird_width = 32; 
    const float bird_height = 32;
    const float bullet_width = 16;
    const float bullet_height = 16;

    if(!hummingbird_exists) return;

    if(isColliding(bullet_x, bullet_y, bullet_width, bullet_height,hummingbird_x, hummingbird_y, bird_width, bird_height)){
        bullet_exists = false;
        hummingbird_health -= 1;
        if(hummingbird_health <= 0)
        {hummingbird_sick = true;
        hummingbird_exists = false;}
    }
}
void initializeFlowers(bool flowersInLastTier[], Sprite flowerSprites[], int gameRows, Texture& flowerTexture){
    for(int i = 0; i < gameRows; i++){
        flowersInLastTier[i] = false;
        flowerSprites[i].setTexture(flowerTexture);
    }
}
void placeFlowerAtTile(bool flowersInLastTier[], Sprite flowerSprites[], int tileIndex){
    flowersInLastTier[tileIndex] = true;
    flowerSprites[tileIndex].setPosition(tileIndex * 32, 544); //y=544 last tier line
}
//Attempts to find a free tile near bee_x and place a flower
bool findFreeTileAndPlaceFlower(bool flowersInLastTier[], Sprite flowerSprites[], float bee_x, int gameRows){
    int beeTile = (bee_x / 32);
    if(!flowersInLastTier[beeTile]){
        placeFlowerAtTile(flowersInLastTier, flowerSprites, beeTile);
        return true;
    }
    int left = beeTile - 1;
    int right = beeTile + 1;
while(left >= 0 || right < gameRows){
    if(right < gameRows && !flowersInLastTier[right]){
        placeFlowerAtTile(flowersInLastTier, flowerSprites, right);
        return true;
    }
    if(left >= 0 && !flowersInLastTier[left]){
        placeFlowerAtTile(flowersInLastTier, flowerSprites, left);
        return true;
    }
left--;
right++;
}
    return false;
}

void handleBeeFlowerPlacement(bool& firstBeeFlowerDone, bool flowersInLastTier[], Sprite flowerSprites[], int gameRows, float& bee_x, float& bee_y, bool& bee_exists, bool& bee_movingRight){
    //if this is the first bee placing flowers:
if(!firstBeeFlowerDone){
    //Place two flowers at left and right borders
    placeFlowerAtTile(flowersInLastTier, flowerSprites, 0);
    placeFlowerAtTile(flowersInLastTier, flowerSprites, gameRows-1);
    firstBeeFlowerDone = true;
} else {
    //Subsequent bees place only one flower
    findFreeTileAndPlaceFlower(flowersInLastTier, flowerSprites, bee_x, gameRows);
}

    //After placing flower(s), reverse direction so the bee exits
    bee_movingRight = !bee_movingRight;
    //The bee will move horizontally until it exits the screen in the movement function.
}
void drawFlowers(RenderWindow& window, const bool flowersInLastTier[], const Sprite flowerSprites[], int gameRows){
    for(int i = 0; i < gameRows; i++){
        if(flowersInLastTier[i]){
            window.draw(flowerSprites[i]);
        }
    }
}
int hummingBirdpoints( bool isRed,float yCoordinates){
if(yCoordinates <= 128){
        if(isRed)	
            return 2000;
        else
            return 1000;
        }
else if(yCoordinates <= 160){
		if(isRed)
		    return 1800; 
		else 
		    return 800;
		}
else {
		if(isRed)
		    return 1500;
		else
		    return 500;  
		}	
}
void bonuscan(int score,int& nextBonusScore,int& canCount){
	if(score >= nextBonusScore){
canCount++; //Grant an additional can
//Update nextBonusScore based on current threshold
	if(nextBonusScore == 20000){
	    nextBonusScore = 40000;}
	else if(nextBonusScore == 40000){
	    nextBonusScore = 80000;}
    else {
	    nextBonusScore += 80000;}
	}
}
void drawScore(RenderWindow& window, Font& font, int score){
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(Color::Yellow);
    scoreText.setOutlineColor(Color::Black);
    scoreText.setOutlineThickness(1);
    scoreText.setString("Score: " + to_string(score));
	int x = resolutionX/4*2.5; 
	int y = resolutionY-64; 
    scoreText.setPosition(x,y);
    window.draw(scoreText);
}
void loadHighScores(const std::string& filename, std::string names[], int scores[], const int MAX_HIGH_SCORES){
    std::ifstream inputFile(filename);
    if(inputFile.is_open()){
        for(int i = 0; i < MAX_HIGH_SCORES; ++i){
            inputFile >> names[i];
            inputFile >> scores[i];
        }
        inputFile.close();
    } else {
        //if file doesn't exist, initialize with default values
        for(int i = 0; i < MAX_HIGH_SCORES; ++i){
            names[i] = "unamed_";
            scores[i] = 0;
        }
    }
}

void saveHighScores(const std::string& filename, const std::string names[], const int scores[], const int MAX_HIGH_SCORES){
    std::ofstream outputFile(filename);
    if(outputFile.is_open()){
        for(int i = 0; i < MAX_HIGH_SCORES; ++i){
            outputFile << names[i] << " " << scores[i] << "\n";
        }
        outputFile.close();
    }
}
bool updateHighScores(int playerScore, std::string& playerName, std::string names[], int scores[], const int MAX_HIGH_SCORES){
    //Check if the player's score qualifies for high scores
    for(int i = 0; i < MAX_HIGH_SCORES; i++){
        if(playerScore > scores[i]){ 
        
        for(int j = MAX_HIGH_SCORES - 1; j > i; j--)
        {names[j] = names[j - 1];
        scores[j] = scores[j - 1];}
        //Insert the new high score
        names[i] = playerName;
        scores[i] = playerScore;
        return true; //High score was updated
        }
    }
    
    return false; //No update needed

}

void displayHighScores(sf::RenderWindow& window, sf::Font& font, const std::string names[], const int scores[], const int MAX_HIGH_SCORES){
    //Create a semi-transparent background for better readability
    RectangleShape background(sf::Vector2f(600, 500));
    background.setFillColor(sf::Color(0, 0, 0, 150)); //Semi-transparent black
    background.setPosition(180, 70); //Centered position
    window.draw(background);
    //Title text
    sf::Text title;
    title.setFont(font);
    title.setString("High Scores");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(300, 100);
    window.draw(title);
    //Display each high score
    sf::Text entries[MAX_HIGH_SCORES];
    for(int i = 0; i < MAX_HIGH_SCORES; ++i){
        entries[i].setFont(font);
        entries[i].setCharacterSize(30);
        entries[i].setFillColor(sf::Color::White);
        entries[i].setPosition(300, 160 + i * 40);
        entries[i].setString(std::to_string(i + 1) + ". " + names[i] + " - " + std::to_string(scores[i]));
        window.draw(entries[i]);
    }
}
void promptPlayerName(RenderWindow& window, Font& font, std::string& playerName){
    bool nameEntered = false;
    sf::String enteredName = "";

    //prompt text to be entered by user
    sf::Text prompt;
    prompt.setFont(font);
    prompt.setString("Enter Your Name:");
    prompt.setCharacterSize(40);
    prompt.setFillColor(Color::Yellow);
    prompt.setPosition(300, 300);
    window.draw(prompt);
    window.display();

    //Create text to display the entered name
    sf::Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(40);
    nameText.setFillColor(Color::White);
    nameText.setPosition(300, 350);

while(!nameEntered && window.isOpen()){
Event event;
while(window.pollEvent(event)){
    if(event.type == Event::Closed){
        window.close();
        return;
    }
if(event.type == Event::TextEntered){
if(event.text.unicode == 13){ //Enter key
    if(!enteredName.isEmpty()){
        nameEntered = true;
        playerName = enteredName.toAnsiString();
    }
}
else if(event.text.unicode == 8){ //Backspace
        if(!enteredName.isEmpty()){
            enteredName.erase(enteredName.getSize() - 1, 1);
        }
    }
else if(event.text.unicode < 128 && enteredName.getSize() < 10){ //Limit name length
        //Only allow alphanumeric characters
    if(isalnum(event.text.unicode)){
        enteredName += static_cast<char>(event.text.unicode);
         }
        }
    }
}
//Update the name text
nameText.setString(enteredName);
window.draw(prompt);
window.draw(nameText);
window.display();
window.clear();
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||========    ||     ||    |||||     >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>/////////////////////  
/////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||            ||     ||    ||  ||    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>/////////////////////
/////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||            |||    ||    ||   ||   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>///////////////////// 
/////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||========    ||  |  ||    ||    ||  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>/////////////////////  
/////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||            ||   | ||    ||    ||  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>/////////////////////    
/////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||            ||    |||    ||   ||   >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>///////////////////// 
/////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<||========    ||     ||    ||||||    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>/////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

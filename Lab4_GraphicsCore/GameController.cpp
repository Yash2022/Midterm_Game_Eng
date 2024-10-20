// Ramanooj
#include "GameController.h"
#include "AssetController.h"
#include "SpriteSheet.h"
#include <fstream>
#include <cstdlib>

GameController::GameController()
    : m_currentLevel(1),
    m_isRunning(true),
    m_timeSinceLastSave(0.0f),
    m_renderer(nullptr),
    m_timing(nullptr),
    m_font(nullptr),
    m_stoneSpawnTimer(0.0f),
    m_stoneSpawnInterval(0.5f)
{
}

GameController::~GameController()
{
    for (auto warrior : m_warriors)
    {
        delete warrior;
    }
    m_warriors.clear();

    for (auto stone : m_stones)
    {
        delete stone;
    }
    m_stones.clear();

    if (m_font)
    {
        m_font->Shutdown();
        delete m_font;
        m_font = nullptr;
    }

    if (m_renderer)
    {
        m_renderer->Shutdown();
        delete m_renderer;
        m_renderer = nullptr;
    }

    if (m_timing)
    {
        delete m_timing;
        m_timing = nullptr;
    }

    AssetController::Instance().Shutdown();
}

void GameController::RunGame()
{
    const int targetFPS = 45;  // Target FPS
    const float targetFrameTime = 1.0f / targetFPS;  // Target time per frame

    AssetController::Instance().Initialize(10000000);

    m_renderer = new Renderer();
    if (!m_renderer->Initialize(1920, 1080))
    {
        std::cerr << "Failed to initialize renderer." << std::endl;
        m_isRunning = false;
        return;
    }

    m_timing = new Timing();

    m_font = new TTFont();
    if (!m_font->Initialize("../Assets/Fonts/arial.ttf", 20))
    {
        std::cerr << "Failed to initialize font!" << std::endl;
        m_isRunning = false;
        return;
    }

    LoadLevel1();

    while (m_isRunning)
    {
        m_timing->Tick();
        float deltaTime = m_timing->GetDeltaTime();

        while (SDL_PollEvent(&m_sdlEvent))
        {
            if (m_sdlEvent.type == SDL_QUIT)
            {
                m_isRunning = false;
            }
        }

        Update(deltaTime);

        if (!m_isRunning)
        {
            break;
        }

        Render();

        m_renderer->Present();

        // Cap the FPS by waiting if necessary
        float frameTime = m_timing->GetDeltaTime();
        if (frameTime < targetFrameTime)
        {
            SDL_Delay(static_cast<Uint32>((targetFrameTime - frameTime) * 1000));  // Delay in milliseconds
        }
    }
}

void GameController::LoadLevel1()
{
    m_currentLevel = 1;

    for (auto warrior : m_warriors)
    {
        delete warrior;
    }
    m_warriors.clear();

    for (auto stone : m_stones)
    {
        delete stone;
    }
    m_stones.clear();

    SpriteSheet* warriorSheet = new SpriteSheet(m_renderer->GetSDLRenderer());
    if (!warriorSheet->Load("../Assets/Textures/Warrior.tga"))
    {
        std::cerr << "Failed to load Warrior.tga" << std::endl;
        m_isRunning = false;
        return;
    }
    warriorSheet->SetGridSize(17, 6, 69, 44);

    for (int i = 0; i < 10; ++i)
    {
        float speed = 30.0f + static_cast<float>(rand() % 21);
        float animSpeed = 4.0f + (speed - 30.0f) * (1.0f / 20.0f);
        Warrior* warrior = new Warrior(warriorSheet, speed, animSpeed);
        warrior->SetPosition(-warrior->GetWidth(), 50.0f + static_cast<float>(i) * 50.0f);
        warrior->SetScale(1.0f);
        m_warriors.push_back(warrior);
    }

    m_timeSinceLastSave = 0.0f;
}

void GameController::LoadLevel2()
{
    std::cout << "Loading Level 2..." << std::endl;
    m_currentLevel = 2;
    
    
    for (auto stone : m_stones)
    {
        delete stone;
    }
    m_stones.clear();

    m_stoneSpawnTimer = m_stoneSpawnInterval;
    m_stoneSpawnInterval = 0.5f;

    m_timeSinceLastSave = 0.0f;

   
    m_stoneSpriteSheet = new SpriteSheet(m_renderer->GetSDLRenderer());
    if (!m_stoneSpriteSheet->Load("../Assets/Textures/Stone.tga"))
    {
        std::cerr << "Failed to load Stone.tga" << std::endl;
        m_isRunning = false;
        return;
    }
    m_stoneSpriteSheet->SetGridSize(1, 8, 64, 64);

    std::cout << "Level 2 loaded successfully." << std::endl;
}
    
void GameController::Update(float deltaTime)
{
    m_timeSinceLastSave += deltaTime;

    bool levelChanged = false;

    int warriorsAtEnd = 0;   
    int totalWarriors = 0;      

    for (auto it = m_warriors.begin(); it != m_warriors.end(); )
    {
        Warrior* warrior = *it;
        warrior->Update(deltaTime);

        if (warrior->IsDead() && warrior->AnimationFinished())
        {
            delete warrior;
            it = m_warriors.erase(it);
        }
        else
        {
            ++totalWarriors;    

            if (warrior->GetPosition().X > 800.0f)
            {
                warriorsAtEnd++;    
            }

            ++it;
        }
    }

    if (totalWarriors > 0 && warriorsAtEnd == totalWarriors)
    {
        if (m_currentLevel == 1)
        {
            LoadLevel2();
            levelChanged = true;
        }
        else
        {
            m_isRunning = false;
        }
    }

    if (levelChanged)
    {
        LoadLevel2();
        std::cout << "Level changed to Level 2." << std::endl;
    }

    if (!m_isRunning)
    {
        return;
    }




    if (m_currentLevel == 2)
    {
        m_stoneSpawnTimer += deltaTime;
        if (m_stoneSpawnTimer >= m_stoneSpawnInterval)
        {
            m_stoneSpawnTimer = 0.0f;

            
            float speed = 50.0f + static_cast<float>(rand() % 21);
            float animSpeed = 5.0f;

            Stone* stone = new Stone(m_stoneSpriteSheet, speed, animSpeed);
            stone->SetPosition(100.0f + static_cast<float>(rand() % 600), -stone->GetHeight());
            stone->SetScale(1.0f);
            m_stones.push_back(stone);

            std::cout << "Stone created at position (" << stone->GetPosition().X << ", " << stone->GetPosition().Y << ")" << std::endl;
        }

        
        for (auto it = m_stones.begin(); it != m_stones.end(); )
        {
            Stone* stone = *it;
            stone->Update(deltaTime);

            bool stoneRemoved = false;
            for (auto warrior : m_warriors)
            {
                if (!warrior->IsDead() && warrior->CollidesWith(stone))
                {
                    warrior->Die();
                    delete stone;
                    it = m_stones.erase(it);
                    stoneRemoved = true;
                    std::cout << "Stone collided with warrior and was removed." << std::endl;
                    break;
                }
            }

            if (stoneRemoved)
            {
                continue;
            }

            if (stone->GetPosition().Y > 600.0f)
            {
                delete stone;
                it = m_stones.erase(it);
                std::cout << "Stone removed from list (out of screen)." << std::endl;
            }
            else
            {
                ++it;
            }
        }

        
        bool allDead = true;
        for (auto warrior : m_warriors)
        {
            if (!warrior->IsDead())
            {
                allDead = false;
                break;
            }
        }
        if (allDead)
        {
            m_isRunning = false;
            std::cout << "All warriors are dead. Ending game." << std::endl;
            return;
        }
    }


    if (m_timeSinceLastSave >= 5.0f)
    {
        std::string filename = (m_currentLevel == 1) ? "Level1.bin" : "Level2.bin";
        SaveGameState(filename);
        m_timeSinceLastSave = 0.0f;
    }
}


void GameController::Render()
{
    m_renderer->SetDrawColor(128, 128, 128, 255);  // Background color
    m_renderer->ClearScreen();

    for (auto warrior : m_warriors)
    {
        warrior->Render(m_renderer);
    }

    for (auto stone : m_stones)
    {
        stone->Render(m_renderer);
    }

    // Set starting x and y coordinates
    int startX = 10;
    int startY = 10;
    int spacing = 150;  // Horizontal spacing between each text item

    // Render FPS horizontally
    std::string fpsText = "FPS: " + std::to_string(static_cast<int>(m_timing->GetFPS()));
    m_font->Write(m_renderer->GetSDLRenderer(), fpsText, { 0, 0, 255, 255 }, { startX, startY });

    // Render Time horizontally, with spacing
    std::string timeText = "Time: " + std::to_string(static_cast<int>(m_timing->GetTotalTime())) + "s";
    m_font->Write(m_renderer->GetSDLRenderer(), timeText, { 0, 0, 255, 255 }, { startX + spacing, startY });

    // Render Auto-Save horizontally, with spacing
    std::string saveText = "Auto-Save in: " + std::to_string(static_cast<int>(5.0f - m_timeSinceLastSave)) + "s";
    m_font->Write(m_renderer->GetSDLRenderer(), saveText, { 0, 0, 255, 255 }, { startX + 2 * spacing, startY });
}

void GameController::SaveGameState(const std::string& filename)
{
 // 
}

void GameController::LoadGameState(const std::string& filename)
{
 //
}

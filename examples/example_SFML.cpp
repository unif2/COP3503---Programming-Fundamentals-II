/*
    sf::Sprite shuffleButton(TextureManager::GetTexture("btnShuffle"));
    shuffleButton.setPosition(0, window.getSize().y - shuffleButton.getTextureRect().height);

    sf::Sprite resetButton(TextureManager::GetTexture("btnReset"));
    int xPosition = shuffleButton.getTextureRect().width;
    int yPosition = window.getSize().y - resetButton.getTextureRect().height;
    resetButton.setPosition(xPosition, yPosition);


    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Red);
    //shape.setPosition(400, 200);


    // Drawing a Sprite, part 1: Load a texture from a file
    sf::Texture texture;
    string filePath = "images/feynman_diagram.png"; // Relative path
    texture.loadFromFile(filePath);

    // Drawing a Sprite, part 2: Create a sf::Sprite with the texture passed to its constructor
    sf::Sprite sprite(texture); // Draw this to the screen, specifically the sf::Texture that it is associated with

    vector<sf::Texture> textures(7);
    vector<sf::Sprite> cards;
    // or vector<Card> cards;
    for (int num = 2, i = 0; num <= 8; num++, i++)
    {
        string filePath = "cards/"; //TextureManager class assumes images director at the beginning and .png files
        filePath += to_string(num);
        filePath += "_of_diamonds";

        textures[i].loadFromFile(filePath);
        
        sf::Sprite card(textures[i]);
        // sf::Sprite card(TextureManager::GetTexture(filePath));
        cards.push_back(card);

    }

    // As long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        // Work with the operating system (OS) to handle events properly
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // The mouse button was pressed.. but which mouse button?
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Specifically, the left button was pressed...
                    // Print the mouse position to the console
                    // Get position relative to the window
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    cout << "X: " << position.x << " Y: " << position.y << endl;

                    // If (Shuffle Button was clicked)
                    if (shuffleButton.getGlobalBounds().contains(position.x, position.y))
                    {
                        deck.Shuffle();
                    }

                    // If (Reset Button was clicked)
                    if (resetButton.getGlobalBounds().contains(position.x, position.y))
                    {
                        deck.Reset();
                    }

                    // Toggle the card
                    //someCard.isFaceUp = !someCard.isFaceUp;

                    // Check to see if the mouse is within the boundaries of a sprite
                    for (int i = 0; i < 2; i++)
                    {
                        if (someCards[i].GetSpriteRect().contains(position.x, position.y))
                        {
                            someCards[i].isFaceup = !someCards[i].isFaceup;
                        }
                    }
                }
            }
        }

        // Drawing sub-step

        // 1. Erase everything that was previously drawn
        window.clear(sf::Color(150, 150, 150));

        // 2. Draw however many things you want to appear on screen
        for (int i = 0; i < 10; i++)
        {
            shape.setPosition(shape.getRadius() * 2 * i, i * 25);
            window.draw(shape);
        }

        // Drawing a Sprite, part 3: call the .draw() function of the window (sf::RenderWindow), pass the Sprite
        sprite.setPosition(0, 0);
        window.draw(sprite);
        sprite.setPosition(50, 50);
        window.draw(sprite);
        sprite.setPosition(100, 100);
        window.draw(sprite);

        // Vector2i == X/Y coordinates, stored as integers
        // Vector2f == X/Y coordinates, stored as floats
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // Draw this at the position of the mouse cursor
        sprite.setPosition(mousePosition.x, mousePosition.y);
        window.draw(sprite);

        for (unsigned int i = 0; i < cards.size(); i++)
        {
            cards[i].setPosition(i * 50, i * 50);

            window.draw(cards[i]);
        }

        for (int i = 0; i < 2; i++)
        {
            if (someCards[i].isFaceup)
                window.draw(someCards[i].cardFaceup);
            else
                window.draw(someCards[i].cardFacedown);
        }

        // What does this do?  Don't know here, but the function (and its object) do!
        deck.Display(window);

        window.draw(shuffleButton);
        window.draw(resetButton);

        //someCard.Draw(window); // Or put the lines above in this function so that those don't have to be public
        // 3. Present all of the stuff you drew to the screen to the display device (i.e. the monitor)
        window.display();
    }
    cout << "Ending Vince Velocci's program (UFID: 50682042)" << endl;
    // Clear out any textures before the program ends
    TextureManager::Clear();
    */
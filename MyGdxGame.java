package com.mygdx.game;
import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.files.FileHandle;
import com.badlogic.gdx.graphics.*;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.Sprite;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.mygdx.game.Cards.*;
import com.mygdx.game.Cards.Colors;
import com.mygdx.game.Managers.MusicPlayer;
import com.mygdx.game.Players.AI;
import com.mygdx.game.Players.Player;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Random;

public class MyGdxGame extends ApplicationAdapter{
    private SpriteBatch batch;
    private BitmapFont font;
    private ShapeRenderer shapeRenderer;
    private Sound placementSound,highlightSound;
    Texture backgroundTexture = null;
    private Viewport viewport;
    private Camera camera;
    private Stage stage;

    private GameManager gameManager;
    private Player player;
    private AI machine;
    private int startingMachineScore=0;
    private int startingPlayerScore=0;
    private boolean mouseOverHighlightedCard = false;
    private int numbersOnDeck = -1;
    private int numbersOfCardsInHand = -1;

    @Override
    public void create() {
        camera = new PerspectiveCamera();
        viewport = new FitViewport(800, 480,camera);
        stage = new Stage(viewport);
        batch = new SpriteBatch();
        shapeRenderer = new ShapeRenderer();
        LoadRandomBackgroundImage();
        LoadSounds();
        font = new BitmapFont();
        font.setColor(Color.WHITE);
        MusicPlayer musicPlayer = new MusicPlayer();
        musicPlayer.loadSongs(new String[]{"pookatori_and_friends.mp3", "ready_set_play.mp3","threshold.mp3"});
        musicPlayer.play();
//MyCardGame game has:
    numbersOnDeck = 5;
    String[] typeNames = {"Water", "Fire", "Earth"};
    numbersOfCardsInHand = 3;
    int rounds = 30;
    int roundTimer = 30;
    StartingScore(100, 400);
//WinRoundCondition(WinRoundRule)
//WinGameCondition(standard)
//CardsDesign(myDesign)
//BackgroundDesign(standard)
    Deck deck = new Deck(typeNames, numbersOnDeck);
    gameManager = new GameManager(typeNames, numbersOnDeck, rounds, roundTimer);
    deck.generateDeck();
//WinRoundRule for game:
    gameManager.addTypeRelation("Fire", "Earth");
    gameManager.addTypeRelation("Earth", "Water");
    gameManager.addTypeRelation("Water", "Fire");
//myDesign design has:
    deck.assignColorToType("Water", Colors.CORNFLOWER, true);
    deck.assignColorToType("Fire", Colors.MAGENTA, true);
    deck.assignColorToType("Earth", Colors.LIME, true);
        player = new Player(startingPlayerScore, numbersOfCardsInHand);
        machine = new AI(startingMachineScore, numbersOfCardsInHand);
        gameManager.dealInitialCards(player, numbersOfCardsInHand, deck);
        gameManager.dealInitialCards(machine, numbersOfCardsInHand, deck);
    }

    @Override
    public void render() {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        stage.draw();
        // Draw player cards and Background using SpriteBatch
        batch.begin();
        if (backgroundTexture != null) {
            Sprite backgroundSprite = new Sprite(backgroundTexture,Gdx.graphics.getWidth(),Gdx.graphics.getHeight());
            backgroundSprite.draw(batch);
        }
        drawPlayerCardsBatch(player, 50, 0);
        batch.end();
        // Draw scores
        batch.begin();
        drawScores();
        batch.end();

        // Resaltar la carta bajo el mouse
        highlightCardUnderMouse();

        // Draw player cards using ShapeRenderer
        shapeRenderer.begin(ShapeRenderer.ShapeType.Filled);
        drawPlayerCardsShape(player, 50, Gdx.graphics.getHeight() - 450);
        shapeRenderer.end();
        float mouseX = Gdx.input.getX();
        float mouseY = Gdx.graphics.getHeight() - Gdx.input.getY();
        // Handle input for playing a round
        if (Gdx.input.justTouched()) {
            Card selectedCard = getSelectedCard(mouseX, mouseY);
            if (selectedCard != null){
                selectedCard.animateToPosition((float) viewport.getScreenX() /2, (float) viewport.getScreenY() /2,2f);
                stage.addActor(selectedCard);
                System.out.println("Pressed " + selectedCard.toString());
                placementSound.play(0.5f);
                gameManager.playRound(selectedCard,player,machine);
            }
        }
    }

    @Override
    public void resize(int width, int height) {
        viewport.update(width, height, true);
        for (Card card : player.getCardsInHand())
            updateCardPosition(card);
    }

    private void updateCardPosition(Card card) {
        float initialX = (viewport.getScreenX() - card.getWidth()) / 2f;
        float initialY = 10; // bottom of the screen
        card.setCardPosition(initialX, initialY);
    }

    //Esto puede ser un metodo abstracto que se crea en al GM
    private boolean winGameCondition(Player player) {
        return player.getScore() == 2;
    }

    private void LoadRandomBackgroundImage() {
        FileHandle folder = Gdx.files.internal("assets/Backgrounds/");
        if (folder.exists() && folder.isDirectory()) {
            FileHandle[] backgrounds = folder.list();
            if (backgrounds.length > 1) {
                int index = new Random().nextInt(backgrounds.length);
                backgroundTexture = new Texture(backgrounds[index]);
            } else backgroundTexture = new Texture(backgrounds[0]);
        } else {
            Gdx.app.error("TextureManager", "Backgrounds directory is missing or not found.");
        }
    }

    private void LoadSounds() {
        FileHandle SFXfolder = Gdx.files.internal("assets/Sounds/SFX");
        if (SFXfolder.exists() && SFXfolder.isDirectory()) {
            placementSound = Gdx.audio.newSound(SFXfolder.child("card_impact_sfx.wav"));
            highlightSound = Gdx.audio.newSound(SFXfolder.child("card_highlight_sfx.wav"));
        }
    }

    private void highlightCardUnderMouse() {
        float mouseX = Gdx.input.getX();
        float mouseY = Gdx.graphics.getHeight() - Gdx.input.getY(); // Invertir el eje Y
        shapeRenderer.begin(ShapeRenderer.ShapeType.Line);
        shapeRenderer.setColor(Color.YELLOW); // Definir el color una vez fuera del bucle
        boolean highlightFound = false;
        for (Card card : player.getCardsInHand()) {
            if (card.isTouched(mouseX, mouseY)) {
                card.highlightCard(shapeRenderer); // Resaltar la carta sin llamar a begin/end dentro del bucle
                highlightFound = true;
            }
        }
        if (highlightFound && !mouseOverHighlightedCard && highlightSound != null) {
            highlightSound.play(0.25f);
            mouseOverHighlightedCard = true;
        } else if (!highlightFound) {
            mouseOverHighlightedCard = false;
        }
        shapeRenderer.end();
    }

    private void StartingScore(int playerScore,int machineScore){
        this.startingPlayerScore = playerScore;
        this.startingMachineScore = machineScore;
    }

    private void drawPlayerCardsBatch(Player player, float startX, float startY) {
        float cardSpacing = 20;
        float totalWidth = player.getCardsInHand().size() * (Card.CARD_WIDTH + cardSpacing) - cardSpacing;
        float currentX = startX + (Gdx.graphics.getWidth() - totalWidth) / 2;
        for (Card card : player.getCardsInHand()) {
            card.setCardPosition(currentX, startY);
            card.drawCardBatch(batch, font);
            currentX += Card.CARD_WIDTH + cardSpacing;
        }
    }

    private void drawPlayerCardsShape(Player player, float startX, float startY) {
        float cardSpacing = 20;
        float totalWidth = player.getCardsInHand().size() * (Card.CARD_WIDTH + cardSpacing) - cardSpacing;
        float currentX = startX + (Gdx.graphics.getWidth() - totalWidth) / 2;
        for (Card card : player.getCardsInHand()) {
            card.setCardPosition(currentX, startY);
            //card.drawCardShape(shapeRenderer);
            currentX += Card.CARD_WIDTH + cardSpacing;
        }
    }

    private Card getSelectedCard(float mouseX,float mouseY) {
        for (Card card : player.getCardsInHand()) {
            if (card.isTouched(mouseX,mouseY)) return card;
        }
        return null;
    }

    private void drawScores() {
        String playerScoreText = "Player Score: " + player.getScore();
        String machineScoreText = "Machine Score: " + machine.getScore();
        font.draw(batch, playerScoreText, 50, 50);
        font.draw(batch, machineScoreText, 50, 100);
    }

    @Override
    public void dispose() {
        batch.dispose();
        shapeRenderer.dispose();
        font.dispose();
    }
}
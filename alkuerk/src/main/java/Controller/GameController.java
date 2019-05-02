package Controller;

import Model.GameModel;
import View.GameView;

public class GameController {
    private GameModel model;
    private GameView view;
    private ActionGenerator actionGenerator;

    public GameController(){
        view = new GameView();
        model = new GameModel(view);
        actionGenerator = new ActionGenerator(model);
        view.addButtonAction(actionGenerator);
        view.addNewGameAction(actionGenerator);
    }

    public void start(){
        model.newGame();
    }
}

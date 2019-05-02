package Controller;

import Model.GameModel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ActionGenerator {
    private GameModel model;

    public ActionGenerator(GameModel model){
        this.model = model;
    }

    public ActionListener getButtonAction(int i, int j){
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                model.nextCoords(i, j);
            }
        };
    }

    public ActionListener getNewGameAction(){
        return new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent actionEvent) {
                model.newGame();
            }
        };
    }
}

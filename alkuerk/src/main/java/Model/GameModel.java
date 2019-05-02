package Model;

import View.GameView;

import java.util.Arrays;
import java.util.Scanner;

public class GameModel {
/*
    Map values
    0 - null
    -1 - black
    1 - white
*/
    private int map[][];
    private MapLogicModel mapLogic;
    private GameView view;
    private boolean turn = false;
    private boolean readyTurn = false;
    private int x1, y1;
    private boolean wasCapture[];

    public GameModel(GameView view){
        this.view = view;
        map = new int[5][5];
        mapLogic = new MapLogicModel();
        view.setLoggerText("green");
        wasCapture = new boolean[1];
        wasCapture[0] = false;
    }

    public void nextCoords(int x, int y){
        if(!readyTurn){
            x1 = x;
            y1 = y;
            readyTurn = !readyTurn;
            view.setFocus(x, y);
        } else{
            readyTurn = !readyTurn;
            boolean newTurn;
            newTurn = mapLogic.nextTurn(map, turn, x1, y1, x, y, wasCapture);
            if(newTurn != turn)
                wasCapture[0] = false;
            turn = newTurn;
            view.clearFocus();
            view.setState(map);
            if(turn){
                view.setLoggerText("yellow");
            }else{
                view.setLoggerText("green");
            }
            if(!mapLogic.canTurn(map, turn)){
                int winner = findWinner();
                if(winner == 0){
                    view.setLoggerText("no winner");
                } else if(winner > 0){
                    view.setLoggerText("winner 1");
                } else {
                    view.setLoggerText("winner 2");
                }
            }
        }
    }

    private void fillStartMap(){
        for (int i = 0; i < 5; i++)
            Arrays.fill(map[i],0);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 2; j++)
                map[i][j] = 1;
        for (int i = 0; i < 5; i++)
            for (int j = 3; j < 5; j++)
                map[i][j] = -1;
        map[0][2] = 1;
        map[1][2] = 1;
        map[3][2] = -1;
        map[4][2] = -1;
    }

    public void newGame(){
        fillStartMap();
        view.setState(map);
    }

    private int findWinner(){
        int counter1 = 0;
        int counter2 = 0;
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++){
                if(map[i][j] == 1)
                    counter1++;
                else if(map[i][j] == -1)
                    counter2++;
            }
        return counter1 - counter2;
    }
}

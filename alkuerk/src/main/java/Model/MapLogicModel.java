package Model;

import java.util.ArrayList;

public class MapLogicModel {

    public class Node{
        public int i, j;
        private ArrayList<Node> neighbors;

        public Node(int i, int j){
            neighbors = new ArrayList<Node>();
            this.i = i;
            this.j = j;
        }

        public void addNeigbor(int x, int y){
            if(x >= 0 && x < 5 && y >= 0 && y < 5 && (x != i || y != j)){
                neighbors.add(new Node(x, y));
            }
        }

        public boolean isNeighbor(int x, int y){
            for (int i = 0; i < neighbors.size(); i++){
                Node current = neighbors.get(i);
                if(current.i == y && current.j == x)
                    return true;
            }
            return false;
        }

        public void printNeighbors(){
            System.out.println(neighbors.size());
            for (int i = 0; i < neighbors.size(); i++){
                System.out.print(neighbors.get(i).i);
                System.out.println(neighbors.get(i).j);
            }
        }
    }

    private Node[][] logicMap;

    MapLogicModel(){
        initLogicMap();
    }

    private void initLogicMap(){
        logicMap = new Node[5][5];
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++)
                logicMap[i][j] = new Node(i, j);
        for (int i = 0; i < 5; i++)
            for (int j = 0; j < 5; j++){
                logicMap[i][j].addNeigbor(i - 1, j);
                logicMap[i][j].addNeigbor(i + 1, j);
                logicMap[i][j].addNeigbor(i, j + 1);
                logicMap[i][j].addNeigbor(i, j - 1);
                if((i + j) % 2 == 0){
                    logicMap[i][j].addNeigbor(i - 1, j - 1);
                    logicMap[i][j].addNeigbor(i - 1, j + 1);
                    logicMap[i][j].addNeigbor(i + 1, j - 1);
                    logicMap[i][j].addNeigbor(i + 1, j + 1);
                }
            }
    }

    public void printNeighbors(int i, int j){
        logicMap[i][j].printNeighbors();
    }

    boolean canTurn(int map[][], boolean turn){
        for (int x1 = 0; x1 < 5; x1++)
            for (int x2 = 0; x2 < 5; x2++)
                for (int y1 = 0; y1 < 5; y1++)
                    for (int y2 = 0; y2 < 5; y2++){
                        if(isValidTurn(map, turn, x1, y1, x2, y2)
                                && (canMove(x1, y1, x2, y2) || canCapture(map, turn, x1, y1, x2, y2)))
                            return true;
                    }
        return false;
    }

    boolean canAnyCapture(int map[][], boolean turn){
        for (int x1 = 0; x1 < 5; x1++)
            for (int x2 = 0; x2 < 5; x2++)
                for (int y1 = 0; y1 < 5; y1++)
                    for (int y2 = 0; y2 < 5; y2++){
                        if(isValidTurn(map, turn, x1, y1, x2, y2)
                                && canCapture(map, turn, x1, y1, x2, y2)){
                            return true;
                        }
                    }
        return false;
    }

    boolean isValidTurn(int map[][], boolean turn, int x1, int y1, int x2, int y2){
        int direction = x2 - x1 + y2 - y1;

        if(map[y2][x2] != 0){
            return false;
        }

        int turnNum;
        if(turn)
            turnNum = 1;
        else
            turnNum = -1;

        if(map[y1][x1] != -turnNum){
            return false;
        }

        if(turn){
            if(direction >= 0){
                return false;
            }
        } else{
            if(direction <= 0){
                return false;
            }
        }
        return true;
    }

    boolean canMove(int x1, int y1, int x2, int y2){
        return logicMap[y1][x1].isNeighbor(x2, y2);
    }

    boolean canCapture(int map[][], boolean turn, int x1, int y1, int x2, int y2){
        int directionx = x2 - x1;
        int directiony = y2 - y1;
        int direction = directionx + directiony;
        int directionAbs = Math.abs(direction);
        int directionxAbs = Math.abs(directionx);
        int directionyAbs = Math.abs(directiony);
        int turnNum;

        if(turn)
            turnNum = 1;
        else
            turnNum = -1;

        int xMid = (x2 + x1) / 2;
        int yMid = (y2 + y1) / 2;

        return     (directionAbs == 4
                || directionAbs == 2
                && (directionxAbs == 2 || directionyAbs == 2))
                && logicMap[y1][x1].isNeighbor(xMid, yMid)
                && logicMap[y2][x2].isNeighbor(xMid, yMid)
                && map[yMid][xMid] == turnNum;
    }

    boolean nextTurn(int map[][], boolean turn, int x1, int y1, int x2, int y2, boolean[] wasCapture){
        if(!isValidTurn(map, turn, x1, y1, x2, y2)){
            return turn;
        }

        if((wasCapture[0] || !canAnyCapture(map, turn))
                && canMove(x1, y1, x2, y2)){
            map[y2][x2] = map[y1][x1];
            map[y1][x1] = 0;
            return !turn;
        }

        if(canCapture(map, turn, x1, y1, x2, y2)){
            int xMid = (x2 + x1) / 2;
            int yMid = (y2 + y1) / 2;
            map[yMid][xMid] = 0;
            map[y2][x2] = map[y1][x1];
            map[y1][x1] = 0;
            wasCapture[0] = true;
            return turn;
        }

        return turn;
    }
}

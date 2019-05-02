package View;

import Controller.ActionGenerator;

import javax.swing.*;
import java.awt.*;

public class GameView {

    private final int marginLeft = 20;
    private final int marginTop = 120;
    private MapButton[][] buttons;
    private MapVisual mapVisual;
    private JPanel canvas;
    private Logger logger;
    private int focusx = -1, focusy = -1;
    private NewGameButton newGameButton;

    public GameView() {
        canvas = getCanvas(470, 600);
        buttons = new MapButton[5][5];
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                buttons[i][j] = new MapButton(i, j, 50, 50);
                canvas.add(buttons[i][j]);
            }
        }
        mapVisual = new MapVisual();
        canvas.add(mapVisual);
        logger = new Logger();
        canvas.add(logger);
        newGameButton = new NewGameButton();
        canvas.add(newGameButton);
        canvas.repaint();
    }

    public void setState(int [][]newMap){
        mapVisual.setState(newMap);
        canvas.repaint();
    }

    public void setFocus(int x, int y){
        focusx = x;
        focusy = y;
        canvas.repaint();
    }

    public void clearFocus(){
        focusy = -1;
        focusx = -1;
        canvas.repaint();
    }

    public void setLoggerText(String txt){
        logger.setText(txt);
        canvas.repaint();
    }

    private JPanel getCanvas(int width, int height){
        JFrame jframe = new JFrame();
        jframe.setVisible(true);
        jframe.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jframe.setSize(width+20,height+20);
        jframe.setLocation(400,400);
        jframe.setTitle("Alkuerk");
        JPanel canvas = new JPanel();
        canvas.setSize(width,height);
        canvas.setLayout(null);
        jframe.setContentPane(canvas);
        return canvas;
    }

    public void addButtonAction(ActionGenerator actionGenerator){
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                buttons[i][j].addActionListener(actionGenerator.getButtonAction(i, j));
            }
        }
    }

    private class MapButton extends JButton{
        private JButton button;

        public MapButton(int i, int j, int width, int height){
            super("g");
            setSize(width, height);
            setLocation(marginLeft + i * 2 * width, marginTop + j * 2 * height);
        }

        @Override
        public void paint(Graphics g){

        }
    }

    private class MapVisual extends JComponent{
        private final int boxWidth = 50;
        private int [][] map;
        public MapVisual(){
            this.setLocation(0,0);
            this.setSize(2000,2000);
            map = new int[5][5];
        }

        public void setState(int newMap[][]){
            map = newMap;
        }

        @Override
        public void paintComponent(Graphics g){
            Graphics2D g2 = (Graphics2D)g;
            Font font = new Font("Arial", Font.BOLD, 30);
            g2.setFont(font);
            Color color = Color.BLACK;
            for (int i = 0; i < 5; i++){
                g2.drawLine(
                    marginLeft + 0 * 2 * boxWidth,
                    marginTop + boxWidth/2 + i * 2 * boxWidth,
                    marginLeft + 4 * 2 * boxWidth,
                    marginTop + boxWidth/2 + i * 2 * boxWidth
                );
                g2.drawLine(
                        marginLeft + boxWidth/2 + i * 2 * boxWidth,
                        marginTop + boxWidth/2 + 0 * 2 * boxWidth,
                        marginLeft + boxWidth/2 + i * 2 * boxWidth,
                        marginTop + boxWidth/2 + 4 * 2 * boxWidth
                );
            }
            g2.drawLine(
                    marginLeft + boxWidth/2 + 0 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 0 * 2 * boxWidth,
                    marginLeft + boxWidth/2 + 4 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 4 * 2 * boxWidth
            );
            g2.drawLine(
                    marginLeft + boxWidth/2 + 0 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 4 * 2 * boxWidth,
                    marginLeft + boxWidth/2 + 4 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 0 * 2 * boxWidth
            );
            g2.drawLine(
                    marginLeft + boxWidth/2 + 0 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 2 * 2 * boxWidth,
                    marginLeft + boxWidth/2 + 2 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 0 * 2 * boxWidth
            );
            g2.drawLine(
                    marginLeft + boxWidth/2 + 2 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 0 * 2 * boxWidth,
                    marginLeft + boxWidth/2 + 4 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 2 * 2 * boxWidth
            );
            g2.drawLine(
                    marginLeft + boxWidth/2 + 4 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 2 * 2 * boxWidth,
                    marginLeft + boxWidth/2 + 2 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 4 * 2 * boxWidth
            );
            g2.drawLine(
                    marginLeft + boxWidth/2 + 2 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 4 * 2 * boxWidth,
                    marginLeft + boxWidth/2 + 0 * 2 * boxWidth,
                    marginTop + boxWidth/2 + 2 * 2 * boxWidth
            );
            for (int i = 0; i < 5; i++){
                for (int j = 0; j < 5; j++){
                    switch (map[i][j]){
                        case 1:   color = Color.GREEN;  break;
                        case -1:  color = Color.YELLOW; break;
                        case 0:   color = Color.GRAY;   break;
                    }
                    g2.setColor(color);
                    g2.fillRect(marginLeft + j * 2 * boxWidth,marginTop + i * 2 * boxWidth, boxWidth, boxWidth);
                    g2.setColor(Color.BLACK);
                    g2.drawRect(marginLeft + j * 2 * boxWidth,marginTop + i * 2 * boxWidth, boxWidth, boxWidth);
                }
            }
            if(focusx != -1){
                g2.setColor(Color.BLACK);
                g2.fillRect(marginLeft + focusx * 2 * boxWidth + boxWidth / 4, marginTop + focusy * 2 * boxWidth + boxWidth / 4, boxWidth/2, boxWidth/2);
            }
        }
    }

    private class Logger extends JComponent{
        private String text = "";

        public Logger(){
            this.setLocation(0,20);
            this.setSize(200,100);
        }

        private void setText(String txt){
            text = txt;
        }

        @Override
        public void paintComponent(Graphics g) {
            Graphics2D g2 = (Graphics2D) g;
            Font font = new Font("Arial", Font.BOLD, 30);
            g2.setFont(font);
            g2.setColor(Color.BLACK);
            g2.drawString(text, 50, 50);
        }
    }

    private class NewGameButton extends JButton{
        private JButton button;

        public NewGameButton(){
            super("new game");
            setSize(150, 50);
            setLocation(250, 30);
        }
    }

    public void addNewGameAction(ActionGenerator actionGenerator){
        newGameButton.addActionListener(actionGenerator.getNewGameAction());
    }
}

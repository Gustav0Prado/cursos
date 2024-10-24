import java.awt.*;
import java.awt.event.*;
import java.beans.VetoableChangeListenerProxy;
import java.util.Vector;
import javax.print.DocFlavor.STRING;
import javax.swing.*;

public class main extends JFrame {
    public static void main(String[] args) {
        JFrame janela = new janela();

        janela.setVisible(true);
        WindowListener x = new WindowAdapter (){
            public void windowClosing(WindowEvent e){
                System.exit(0);
            }
        };
        janela.addWindowListener(x);
    }
}

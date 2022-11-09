import java.awt.*;
import java.awt.event.*;
import java.beans.VetoableChangeListenerProxy;
import java.util.Vector;
import javax.print.DocFlavor.STRING;
import javax.swing.*;

public class janela extends JFrame implements ActionListener{
    private JButton B1;
    private JLabel L1;
    private JTextField T1;
    private Vector <String> vet = new Vector<>();

    public janela(){
        B1 = new JButton("Inserir Nome");
        B1.addActionListener(this);
        L1 = new JLabel("Nome");
        T1 = new JTextField("TextField 1");
        // trecho de código a ser substituído nos outros exemplos
        this.getContentPane().setLayout(new FlowLayout());
        this.getContentPane().add(L1);
        this.getContentPane().add(T1);
        this.getContentPane().add(B1);
        // final do trecho de código a ser substituído nos outros exemplos
        this.setLocation(200,200);
        this.setSize(200,150);
    }
    
    public void actionPerformed(ActionEvent e){
        if(e.getSource().equals(B1)){
            vet.add(T1.getText());
        }
    }
}
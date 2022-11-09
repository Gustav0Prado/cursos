import java.awt.*;
import java.awt.event.*;
import java.util.Vector;

import javax.swing.*;

public class janela extends JFrame implements ActionListener{
    private JButton B1;
    private JLabel L1, L2, L3, L4;
    private JTextField T1,T2, T3, T4;
    public Vector <produto> lista = new Vector<>();

    public janela(){
        B1 = new JButton("Inserir Produto");
        B1.addActionListener(this);
        L1 = new JLabel("Nome");
        L2 = new JLabel("Preço");
        L3 = new JLabel("Qtd.");
        L4 = new JLabel("Linha");
        T1 = new JTextField("Nome");
        T2 = new JTextField("Preço");
        T3 = new JTextField("Qtd");
        T4 = new JTextField("Linha");
        // trecho de código a ser substituído nos outros exemplos
        this.getContentPane().setLayout(new FlowLayout());
        this.getContentPane().add(L1);
        this.getContentPane().add(L2);
        this.getContentPane().add(L3);
        this.getContentPane().add(L4);
        this.getContentPane().add(T1);
        T1.addMouseListener(new MouseAdapter(){
            @Override
            public void mouseClicked(MouseEvent e){
                T1.setText("");
            }
        });
        this.getContentPane().add(T2);
        T2.addMouseListener(new MouseAdapter(){
            @Override
            public void mouseClicked(MouseEvent e){
                T2.setText("");
            }
        });
        this.getContentPane().add(T3);
        T3.addMouseListener(new MouseAdapter(){
            @Override
            public void mouseClicked(MouseEvent e){
                T3.setText("");
            }
        });
        this.getContentPane().add(T4);
        T4.addMouseListener(new MouseAdapter(){
            @Override
            public void mouseClicked(MouseEvent e){
                T4.setText("");
            }
        });
        this.getContentPane().add(B1);
        // final do trecho de código a ser substituído nos outros exemplos
        this.setLocation(200,200);
        this.setSize(200,150);
    }
    public void actionPerformed(ActionEvent e){
        if(e.getSource().equals(B1)){
            produto p = new produto(T1.getText(), T3.getText(), Float.parseFloat(T2.getText()), Integer.parseInt(T4.getText()));
            this.lista.add(p);
        }
    }

    public static void main(String[] args) {
        JFrame janela = new janela();
        janela.setVisible(true);

        WindowListener x = new WindowAdapter(){
            public void windowClosing(WindowEvent e){
                System.exit(0);
            }
        };

        janela.addWindowListener(x);
    }
}
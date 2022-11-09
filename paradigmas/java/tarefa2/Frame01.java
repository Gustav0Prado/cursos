import java.awt.*;
import java.awt.event.*;
import javax.accessibility.Accessible;
import javax.swing.*;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.event.MouseInputAdapter;

public class Frame01 extends JFrame implements ActionListener{

   private JButton B1;
   private JLabel L1, L2, L3;
   private JTextField T1,T2, T3;

   public Frame01(){
      B1 = new JButton("Inserir Aluno");
      B1.addActionListener(this);
      L1 = new JLabel("Nome");
      L2 = new JLabel("Email");
      L3 = new JLabel("GRR");
      T1 = new JTextField("Ex: Joao da Silva");
      T2 = new JTextField("Ex: joao@email.com");
      T3 = new JTextField("Ex: GRRxxxx");
      T1.addMouseListener(new MouseInputAdapter() {
         @Override
         public void mouseClicked(MouseEvent e) {
            T1.setText("");
         }
      });
      T2.addMouseListener(new MouseInputAdapter() {
         @Override
         public void mouseClicked(MouseEvent e) {
            T2.setText("");
         }
      });
      T3.addMouseListener(new MouseInputAdapter() {
         @Override
         public void mouseClicked(MouseEvent e) {
            T3.setText("");
         }
      });
      this.getContentPane().setLayout(new FlowLayout());
      this.getContentPane().add(L1);
      this.getContentPane().add(L2);
      this.getContentPane().add(L3);
      this.getContentPane().add(T1);
      this.getContentPane().add(T2);
      this.getContentPane().add(T3);
      this.getContentPane().add(B1);
      this.setLocation(200,200);
      this.setSize(200,150);
   }

   public void actionPerformed(ActionEvent e){
      CadastraAluno cad = new CadastraAluno();
      //aqui vai o código para tratar os eventos dos botôes
      if (e.getSource() == B1){
         cad.insereAluno(T1.getText(), T2.getText(), T3.getText());
         System.out.println("voce pressionou B1");
         cad.imprimeAlunos();
      }
   }

   public static void main(String[] args) {
      JFrame janela = new Frame01();
      janela.setVisible(true);
      WindowListener x = new WindowAdapter(){
         public void windowClosing(WindowEvent e){
            System.exit(0);
         }
      };
      janela.addWindowListener(x);
   }
}

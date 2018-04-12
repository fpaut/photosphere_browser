import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class MyWin {
	public JPanel create(String name) {
		  JFrame frame = new JFrame(name);
		  frame.setVisible(true);
		  frame.setSize(500,200);
		  frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		  
		  JPanel panel = new JPanel();
		  panel.setLayout(new FlowLayout());
		  JTextField textField = new JTextField();
		  textField.setColumns(10); //On lui donne un nombre de colonnes à afficher
	 
		  frame.add(textField);
		  
		  frame.add(panel);
		  
		  return panel;
	}
}

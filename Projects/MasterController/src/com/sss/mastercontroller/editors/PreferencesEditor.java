package com.sss.mastercontroller.editors;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import com.sss.mastercontroller.main.MasterController;

public class PreferencesEditor implements ChangeListener, ActionListener {
	
	private JFrame frame = new JFrame("Preferences");
	private JTextArea definition = new JTextArea(4, 1);
	private JPanel defPanel = new JPanel();
	//private JPanel editorPanel = new JPanel();
	private JPanel buttonPanel = new JPanel();
	
	private JButton exit = new JButton("Close");
	private JButton apply = new JButton("Apply");
	
	//private GridBagConstraints editorCon = new GridBagConstraints();
	
	private int type;

	public PreferencesEditor(String item, String defi, int type) {
		frame.setTitle("Edit " + item + " preferences");
		frame.setSize(400, 600);
		frame.setAlwaysOnTop(true);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setLocationRelativeTo(null);
		//frame.setUndecorated(true);
		frame.setResizable(false);
		frame.setLayout(new GridBagLayout());
		this.type = type;
		
		GridBagConstraints definitionCon = new GridBagConstraints();
		definitionCon.anchor = GridBagConstraints.NORTH;
		definitionCon.fill = GridBagConstraints.HORIZONTAL;
		definitionCon.gridx = 0;
		definitionCon.gridy = 0;
		definitionCon.weightx = 1.0f;
		definitionCon.weighty = 1.0f;
		
		//definition
		defPanel.setLayout(new GridBagLayout());
		defPanel.add(definition, definitionCon);
		definition.setText(defi);
		definition.setWrapStyleWord(true);
		frame.add(defPanel, definitionCon);
		//editor
		//editorPanel = new JPanel();
		//buttons
		GridBagConstraints buttonCon = new GridBagConstraints();
		buttonCon.anchor = GridBagConstraints.SOUTH;
		buttonCon.fill = GridBagConstraints.HORIZONTAL;
		buttonCon.gridx = 0;
		buttonCon.gridy = 0;
		buttonCon.weightx = 1.0f;
		buttonCon.weighty = 1.0f;
		buttonPanel.setLayout(new BorderLayout());
		
		buttonPanel.add(exit, BorderLayout.WEST);
		exit.addActionListener(this);
		buttonPanel.add(apply, BorderLayout.EAST);
		apply.addActionListener(this);
		frame.add(buttonPanel, buttonCon);
		
		definition.setEditable(false);
		definition.setBackground(Color.BLUE);
		definition.setForeground(Color.WHITE);
		
		frame.setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		if (event.getSource().equals(exit)) {
			frame.dispose();
			MasterController ms = MasterController.getMasterController();
			ms.frame.setEnabled(true);
			ms.clearItems();
			ms.showItems(type);
		} else if (event.getSource().equals(apply)) {
			// this is where all the code will go to send information to the server
			
			//end it here
			frame.dispose();
			MasterController ms = MasterController.getMasterController();
			ms.frame.setEnabled(true);
			ms.clearItems();
			ms.showItems(type);
		}
	}

	@Override
	public void stateChanged(ChangeEvent event) {
		
	}
}
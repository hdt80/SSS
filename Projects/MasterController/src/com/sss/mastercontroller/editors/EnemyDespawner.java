package com.sss.mastercontroller.editors;

import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JPanel;

import com.sss.mastercontroller.main.MasterController;

public class EnemyDespawner implements ActionListener {
	
	private JFrame frame = new JFrame("Despawner");
	private JPanel editorPanel = new JPanel();
	private JPanel buttonPanel = new JPanel();
	private JButton exit = new JButton("Exit");
	private JButton apply = new JButton("Apply");
	private GridBagConstraints editorCon = new GridBagConstraints();
	private int selectedEnemy;
	private String[] enemiesInGame;
	private JComboBox enemiesInGameBox = new JComboBox();
	
	private MasterController ms;
	
	public EnemyDespawner() {
		ms = MasterController.getMasterController();
		//set up the gbc
		editorCon.anchor = GridBagConstraints.CENTER;
		editorCon.fill = GridBagConstraints.HORIZONTAL;
		editorCon.gridx = 0;
		editorCon.gridy = 0;
		editorCon.weightx = 1.0f;
		editorCon.weighty = 1.0f;
		//set up the frame
		frame.setTitle("Enemy despawner");
		frame.setSize(400, 400);
		frame.setAlwaysOnTop(true);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setLocationRelativeTo(null);
		frame.setUndecorated(true);
		frame.setResizable(false);
		frame.setLayout(new GridBagLayout());
		//set up the editor
		editorPanel = new JPanel();
		setDespawner();
		//set up the buttons
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

		frame.setVisible(true);
	}
	
	private void setDespawner() {
		editorPanel.setLayout(new GridLayout(3, 2));
		//combobox
		
	}

	public void actionPerformed(ActionEvent event) {
		
	}
}
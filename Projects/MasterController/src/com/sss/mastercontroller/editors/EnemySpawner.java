package com.sss.mastercontroller.editors;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextArea;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import com.sss.mastercontroller.connections.Connection;
import com.sss.mastercontroller.io.Print;
import com.sss.mastercontroller.main.MasterController;

public class EnemySpawner implements ChangeListener, ActionListener {
	
	private JFrame frame = new JFrame("Spawner");
    private JTextArea definition = new JTextArea();
    private JPanel defPanel = new JPanel();
    private JPanel editorPanel = new JPanel();
    private JPanel buttonPanel = new JPanel();
    
    private JButton exit = new JButton("Close");
    private JButton apply = new JButton("Apply");
    
    private int enemyType;
    
    private Connection connection;
    
    private GridBagConstraints editorCon = new GridBagConstraints();
    
    //variables -- will be changed through editor
    private int _spawncount = 1, _minspawncount = 0, _maxspawncount = 25;
    private int _initialhealth = 100, _mininitialhealth = 10, _maxinitialhealth = 200;
    
    //tools for editor
    private JSlider spawncountSlider = new JSlider(); private JLabel spawncountLabel = new JLabel("Spawn Count [" + _spawncount + "]");
    private JSlider initialhealthSlider = new JSlider(); private JLabel initialhealthLabel = new JLabel("Enemy Spawn Health [" + _initialhealth + "]");
    
    private MasterController ms;
    
	public EnemySpawner(String item, String defi, int enemy) {
		ms = MasterController.getMasterController();
		connection = MasterController.getConnection();
		enemyType = enemy;
		//initialize editor gridbag
		editorCon.anchor = GridBagConstraints.CENTER;
		editorCon.fill = GridBagConstraints.HORIZONTAL;
		editorCon.gridx = 0;
		editorCon.gridy = 0;
		editorCon.weightx = 1.0f;
		editorCon.weighty = 1.0f;	
		//initialize frame
		frame.setTitle(item + " spawner");
		frame.setSize(400, 400);
		frame.setAlwaysOnTop(true);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setLocationRelativeTo(null);
		frame.setUndecorated(true);
		frame.setResizable(false);
		frame.setLayout(new GridBagLayout());
		
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
		frame.add(defPanel, definitionCon);
		//editor
		editorPanel = new JPanel();
		setEnemy();
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
	
	private void setEnemy() {
		editorPanel.setLayout(new GridLayout(3, 2));
		//spawn count
		editorPanel.add(spawncountLabel, editorCon);
		spawncountSlider = configureSlider(_spawncount, _minspawncount, _maxspawncount, "Change how many enemies are desired to spawn.", 5, true, false);
		editorPanel.add(spawncountSlider, editorCon);
		//initial health
		editorPanel.add(initialhealthLabel, editorCon);
		initialhealthSlider = configureSlider(_initialhealth, _mininitialhealth, _maxinitialhealth, "Change how much health the enemy will spawn with", 10, true, false);
		editorPanel.add(initialhealthSlider, editorCon);
		//add to frame
		frame.add(editorPanel, editorCon);
	}
	
	private JSlider configureSlider(int value, int min, int max, String tip, int ticks, boolean showMarks, boolean snapToTick) {
		JSlider slider = new JSlider();
		slider.setValue(value);
		slider.setMinimum(min);
		slider.setMaximum(max);
		slider.setToolTipText(tip);
		slider.setPaintLabels(showMarks);
		slider.setMajorTickSpacing(ticks * 2);
		slider.setMinorTickSpacing(ticks);
		slider.setPaintTicks(showMarks);
		slider.setSnapToTicks(snapToTick);
		slider.addChangeListener(this);
		return slider;
	}

	@Override
	public void stateChanged(ChangeEvent event) {
		if (event.getSource().equals(spawncountSlider)) {
			_spawncount = spawncountSlider.getValue();
			spawncountLabel.setText("Spawn Count [" + _spawncount + "]");
		} else if (event.getSource().equals(initialhealthSlider)) {
			_initialhealth = initialhealthSlider.getValue();
			initialhealthLabel.setText("Enemy Spawn Health [" + _initialhealth + "]");
		}
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		if (event.getSource().equals(exit)) {
			frame.dispose();
			ms.frame.setEnabled(true);
			ms.clearItems();
		} else if (event.getSource().equals(apply)) {
			// this is where all the code will go to send information to the server
			Print.debug("Sending spawn event to the server.");
			Print.debug("We are going to spawn " + _spawncount + " of enemy type " + ms.enemies.getEnemy(enemyType) + ".");
			connection.sendEventToServer("0;" + enemyType + ";" + _spawncount + ";" + _initialhealth
					+ ";");
			//end it here
			frame.dispose();
			MasterController ms = MasterController.getMasterController();
			ms.frame.setEnabled(true);
			ms.clearItems();
		}
	}
}
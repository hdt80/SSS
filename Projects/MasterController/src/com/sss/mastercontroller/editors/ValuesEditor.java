package com.sss.mastercontroller.editors;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
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

public class ValuesEditor implements ChangeListener, ActionListener {
	
	private JFrame frame = new JFrame("Values");
    private JTextArea definition = new JTextArea();
    private JPanel defPanel = new JPanel();
    private JPanel editorPanel = new JPanel();
    private JPanel buttonPanel = new JPanel();
    
    private JButton exit = new JButton("Close");
    private JButton apply = new JButton("Apply");
    
    private int type;
    private int enemyType;
    
    private Connection connection;
    
    private GridBagConstraints editorCon = new GridBagConstraints();
    
    //variables -- will be changed through editor
    private int _pullforce = 0, _minpullforce = 0, _maxpullforce = 200;
    private int _pushforce = 0, _minpushforce = 0, _maxpushforce = 200;
    private int _spawncount = 1, _minspawncount = 0, _maxspawncount = 50;
    private int _damageratio = 50, _mindamageratio = 0, _maxdamageratio = 75; //1.0f = 100% of health
    private int _initialhealth = 100, _mininitialhealth = 10, _maxinitialhealth = 200;
    private int _timedown = 25, _mintimedown = 0, _maxtimedown = 100;
    private int _cracks = 10, _mincracks = 0, _maxcracks = 50;
	private boolean _isfriendly = false;
    
    //tools for editor
    private JSlider pullforceSlider = new JSlider(); private JLabel pullforceLabel = new JLabel("Pull Force [" + _pullforce + "]");
    private JSlider pushforceSlider = new JSlider(); private JLabel pushforceLabel = new JLabel("Push Force [" + _pushforce + "]");
    private JSlider spawncountSlider = new JSlider(); private JLabel spawncountLabel = new JLabel("Spawn Count [" + _spawncount + "]");
    private JSlider damageratioSlider = new JSlider(); private JLabel damageratioLabel = new JLabel("Damage Ratio [" + _damageratio + "]");
    private JSlider initialhealthSlider = new JSlider(); private JLabel initialhealthLabel = new JLabel("Enemy Spawn Health [" + _initialhealth + "]");
    private JSlider timedownSlider = new JSlider(); private JLabel timedownLabel = new JLabel("Time Down (seconds) [" + _timedown + "]");
    private JSlider cracksSlider = new JSlider(); private JLabel cracksLabel = new JLabel("Cracks [" + _cracks + "]");
    private JCheckBox isfriendly = new JCheckBox();
    private JComboBox<String> stations = new JComboBox<String>(); private JLabel timedownStationsLabel = new JLabel("Station Down");
    
	public ValuesEditor(String item, String defi, int type, int enemy) {
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
		frame.setTitle("Edit " + item + " values");
		frame.setSize(400, 400);
		frame.setAlwaysOnTop(true);
		frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		frame.setLocationRelativeTo(null);
		frame.setUndecorated(true);
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
		frame.add(defPanel, definitionCon);
		//editor
		editorPanel = new JPanel();
		switch (type) {
		case 0:
			setEnemy();
			break;
		case 1:
			setIP();
			break;
		case 2:
			setEvent();
			break;
		}
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
		//is friendly
		isfriendly = new JCheckBox("Is Friendly [" + _isfriendly + "]", false);
		isfriendly.addChangeListener(this);
		editorPanel.add(isfriendly, editorCon);
		//add to frame
		frame.add(editorPanel, editorCon);
	}
	
	private void setIP() {
		editorPanel.setLayout(new GridLayout(4, 2));
		//damage ratio
		editorPanel.add(damageratioLabel, editorCon);
		damageratioSlider = configureSlider(_damageratio, _mindamageratio, _maxdamageratio, "Change how much damage the event will inflict on the team ship", 5, true, false);
		editorPanel.add(damageratioSlider, editorCon);
		//cracks
		editorPanel.add(cracksLabel, editorCon);
		cracksSlider = configureSlider(_cracks, _mincracks, _maxcracks, "Change how many cracks the event will add to the team ship window", 5, true, false);
		editorPanel.add(cracksSlider, editorCon);
		//time down
		editorPanel.add(timedownLabel, editorCon);
		timedownSlider = configureSlider(_timedown, _mintimedown, _maxtimedown, "Change how long the effect will put a station down", 5, true, false);
		editorPanel.add(timedownSlider, editorCon);
		//station down
		editorPanel.add(timedownStationsLabel, editorCon);
		stations.addItem("None");stations.addItem("Engineering Station");stations.addItem("Flight Station");stations.addItem("Weapons Station");stations.addItem("Power Station");
		editorPanel.add(stations, editorCon);
		//add to frame
		frame.add(editorPanel, editorCon);
	}
	
	private void setEvent() {
		editorPanel.setLayout(new GridLayout(2, 1));
		//pull force
		editorPanel.add(pullforceLabel, editorCon);
		pullforceSlider = configureSlider(_pullforce, _minpullforce, _maxpullforce, "", 20, true, false);
		editorPanel.add(pullforceSlider, editorCon);
		//push force
		editorPanel.add(pushforceLabel, editorCon);
		pushforceSlider = configureSlider(_pushforce, _minpushforce, _maxpushforce, "", 20, true, false);
		editorPanel.add(pushforceSlider, editorCon);
		
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
		} else if (event.getSource().equals(isfriendly)) {
			_isfriendly = isfriendly.isSelected();
			isfriendly.setText("Is Friendly [" + _isfriendly + "]");
		} else if (event.getSource().equals(damageratioSlider)) {
			_damageratio = damageratioSlider.getValue();
			damageratioLabel.setText("Damage Ratio [" + _damageratio + "]");
		} else if (event.getSource().equals(pullforceSlider)) {
			_pullforce = pullforceSlider.getValue();
			pullforceLabel.setText("Pull Force [" + _pullforce + "]");
			pushforceSlider.setValue(0);
			_pushforce = 0;
		} else if (event.getSource().equals(pushforceSlider)) {
			_pushforce = pushforceSlider.getValue();
			pushforceLabel.setText("Push Force [" + _pushforce + "]");
			pullforceSlider.setValue(0);
			_pullforce = 0;
		} else if (event.getSource().equals(timedownSlider)) {
			_timedown = timedownSlider.getValue();
			if (_timedown == 0) {
				stations.setEnabled(false);
				stations.setSelectedIndex(0);
			} else {
				stations.setEnabled(true);
			}
			timedownLabel.setText("Time Down (seconds) [" + _timedown + "]");
		} else if (event.getSource().equals(cracksSlider)) {
			_cracks = cracksSlider.getValue();
			cracksLabel.setText("Cracks [" + _cracks + "]");
		}
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
			int isfriend = (_isfriendly) ? 1 : 0;
			Print.debug(type + ";" + _pullforce + ";" + _pushforce + ";" + _spawncount + ";"
					+ _damageratio + ";" + _initialhealth + ";" + _timedown + ";" + _cracks
					+ ";" + isfriend + ";" + enemyType + ";");
			connection.sendEventToServer(type + ";" + _pullforce + ";" + _pushforce + ";" + _spawncount + ";"
					+ _damageratio + ";" + _initialhealth + ";" + _timedown + ";" + _cracks
					+ ";" + isfriend + ";" + enemyType + ";");
			//end it here
			frame.dispose();
			MasterController ms = MasterController.getMasterController();
			ms.frame.setEnabled(true);
			ms.clearItems();
			ms.showItems(type);
		}
	}
}
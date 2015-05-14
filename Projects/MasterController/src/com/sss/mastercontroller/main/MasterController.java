package com.sss.mastercontroller.main;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.ListSelectionModel;
import javax.swing.table.TableColumn;

import com.sss.mastercontroller.connections.Addresses;
import com.sss.mastercontroller.connections.Connection;
import com.sss.mastercontroller.editors.PreferencesEditor;
import com.sss.mastercontroller.editors.EnemySpawner;
import com.sss.mastercontroller.io.Print;
import com.sss.mastercontroller.io.TableModel;
import com.sss.mastercontroller.lists.Collisions;
import com.sss.mastercontroller.lists.Enemies;
import com.sss.mastercontroller.lists.Lists;
import com.sss.mastercontroller.lists.Preferences;

public class MasterController implements ActionListener {

	private static Connection connection;
	private static Addresses addresses;
	private Collisions collisions;
	public Enemies enemies;
	private Preferences preferences;
	private static MasterController ms;

	private Container selectionC = new Container();
	private Container itemsC = new Container();

	private JButton[] selections;
	private JButton[] items;

	private JScrollPane pane = new JScrollPane();

	private JPanel buttonPanel = new JPanel();

	private int selectorsNum = 4;
	private int itemsNum = 10;
	private int num = 0;
	private int selectedNum = 0;
	int selectedItemNum = 0;

	private String build = "1.1.31a";

	private boolean[] isSelected;
	private boolean[] isItemSelected;
	private boolean wantChooseIP = true;
	
	public JFrame frame = new JFrame();
	private JTextArea name = new JTextArea();

	public MasterController() {
		name.setText("Sunset Space Simulation - Master Controller " + build);
		collisions = new Collisions();
		enemies = new Enemies();
		addresses = new Addresses();
		preferences = new Preferences();
		if (wantChooseIP) {
			getIPAddress();
		} else {
			connection = new Connection(addresses.getAddress(6), 5003);  	//connect to the default IP address without choice
			connection.sendMessageToServer("MSC"); 							//initialize the client name
		}
	}
	
	public void getIPAddress() {
		//disable frame to avoid mess-ups
		frame.setEnabled(false);
		//now open connection frame
		final JFrame ipframe = new JFrame("Please choose your IP Adress");
		ipframe.setSize(500, 600);
		ipframe.setUndecorated(true);
		ipframe.setLayout(new BorderLayout());
		ipframe.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		ipframe.setResizable(false);
		ipframe.setLocationRelativeTo(null);
		JLabel labl = new JLabel("Choose an IP Address to connect to");
		final JTable table = new JTable(new TableModel());
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		TableColumn columnA = table.getColumn("Index");
        columnA.setMinWidth(25);
        columnA.setMaxWidth(30);
        TableColumn columnB = table.getColumn("IP Addresses");
        columnB.setMinWidth(100);
        columnB.setMaxWidth(100);
        TableColumn columnC = table.getColumn("IP Definition");
        columnC.setMinWidth(350);
        columnC.setMaxWidth(360);
		//table.setRowSelectionAllowed(false);
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		ipframe.add(labl, BorderLayout.NORTH);
		new JScrollPane(table, JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
		ipframe.add(table, BorderLayout.CENTER);
		Container buttons = new Container();
		buttons.setLayout(new BorderLayout());
		JButton select = new JButton("Select IP");
		select.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				if (table.getSelectedRow() >= 0 && table.getSelectedRow() <= addresses.getAddresses()) {
					Print.debug("We are going to connect using ", addresses.getAddress(table.getSelectedRow()), " as an adress through the 5003 port");
					connection = new Connection(addresses.getAddress(table.getSelectedRow()), 5003);
					connection.sendClientIDToServer(); //initialize the client name
					frame.setEnabled(true);
					frame.requestFocus();
					ipframe.dispose();
				}
			}
		});
		JButton exit = new JButton("Exit");
		exit.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		buttons.add(select, BorderLayout.EAST);
		buttons.add(exit, BorderLayout.WEST);
		ipframe.add(buttons, BorderLayout.SOUTH);
		
		ipframe.setAlwaysOnTop(true);
		ipframe.setVisible(true);
	}

	public void start() {
		frame.setUndecorated(true);
		frame.setSize(Toolkit.getDefaultToolkit().getScreenSize());
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// initialize stuff
		initContainers();
		initButtons();
		addButtons();
		initItems(0);
		
		// set frame visible
		frame.setVisible(true);
	}

	private void initItems(int btAmount) {
		// the panel
	    buttonPanel.setLayout(new GridBagLayout());
	    buttonPanel.setSize(400, (int)Toolkit.getDefaultToolkit().getScreenSize().getHeight());
	    // the scroll pane
	    pane.setSize(400, (int)Toolkit.getDefaultToolkit().getScreenSize().getHeight());
	    // GridBagConstraint for button
	    GridBagConstraints constraint = new GridBagConstraints();
	    constraint.anchor = GridBagConstraints.CENTER;
	    constraint.fill = GridBagConstraints.NONE;
	    constraint.gridx = 0;
	    constraint.gridy = GridBagConstraints.RELATIVE;
	    constraint.weightx = 1.0f;
	    constraint.weighty = 1.5f;
	    constraint.insets = new Insets(5, 5, 5, 5);
	    //the buttons
    	items = new JButton[btAmount];
	    for(int i = 0; i < btAmount; i++) {
	    	if (selectedNum == 1) { //enemies
	    		items[i] = new JButton(enemies.getEnemy(i));
		        // other attributes you will set
		        buttonPanel.add(items[i], constraint);
	    	} else if (selectedNum == 0) { //collisions
	    		items[i] = new JButton(collisions.getCollision(i));
	    		//other attributes you will set
	    		buttonPanel.add(items[i], constraint);
	    	} else if (selectedNum == 2) { //preferences
	    		items[i] = new JButton(preferences.getPreferenceName(i));
	    		// other attributes you will set
	    		buttonPanel.add(items[i], constraint);
	    	}
	    	items[i].setBackground(Color.LIGHT_GRAY);
	    	items[i].setForeground(Color.BLACK);
    		items[i].addActionListener(this);
	    }
	    //add it
	    pane.setViewportView(buttonPanel);
	    frame.add(pane, BorderLayout.CENTER);
	    //update
	    pane.updateUI();
	}

	// initialize all the used Containers before giving them buttons and labels,
	// ex...
	private void initContainers() {
		selectionC.setLayout(new GridLayout(selectorsNum, 1));
		selectionC.setVisible(true);
		itemsC.setLayout(new GridLayout(itemsNum, 1));
		itemsC.setVisible(false);
	}

	// initialize all the used buttons to give them names, values, ex...
	private void initButtons() {
		selections = new JButton[selectorsNum]; // there will be `selectorsNum` amount of buttons
		isSelected = new boolean[selectorsNum]; // there will be `selectorsNum` amount of booleans
		isItemSelected = new boolean[num]; // there will be `num` amount of booleans

		selections[0] = new JButton("Collisions");
		selections[1] = new JButton("Enemies");
		selections[2] = new JButton("Preferences");
		selections[3] = new JButton("Exit");

		for (int i = 0; i < selections.length; i++) {
			selectionC.add(selections[i]);
			selections[i].addActionListener(this);
			selections[i].setBackground(Color.LIGHT_GRAY);
			isSelected[i] = false;
		}

		for (int i = 0; i < isItemSelected.length; i++) {
			isItemSelected[i] = false;
		}
	}

	private void addButtons() {
		frame.add(selectionC, BorderLayout.WEST);
		frame.add(itemsC, BorderLayout.CENTER);
		name.setBackground(new Color(190, 190, 190));
		frame.add(name, BorderLayout.EAST);
	}

	public void showItems(int i) {
		if (i == 1) { // show enemies buttons
			num = enemies.getEnemies();
			initItems(num);
		} else if (i == 0) {
			num = collisions.getCollisions();
			initItems(num);
		} else if (i == 2) { //show preferences
			num = preferences.getPreferences();
			initItems(num);
		} else if (i == 3) { //exit button
			Print.debug("Closing the socket.");
			System.exit(-1);
		} else { // some how there was an error
			System.err.println("For some weird reason there was an error on the selection you have tried to make, try choosing the option again.");
		}
	}

	public void clearItems() {
		for (int i = 0; i < items.length; i++) {
			items[i].setVisible(false);
			items[i].setEnabled(false);
		}
	}
	
	private void clearSelections() {
		for (int i = 0; i < selections.length; i++) {
			selections[i].setBackground(Color.LIGHT_GRAY);
			selections[i].setForeground(Color.BLACK);
			isSelected[i] = false;
		}
	}

	private void showValues(int i) {
		frame.setEnabled(false);
		if (selectedNum == 1) { // enemies tab
			new EnemySpawner(enemies.getEnemy(i), enemies.getDefinition(i), i);
		} else {
			System.err.println("For some reason you are still running when you pressed exit button...");
		}
	}
	
	private void showPreferences(int i) {
		frame.setEnabled(false);
		new PreferencesEditor(preferences.getPreferenceName(i), preferences.getPreferenceDefinition(i), selectedNum);
	}

	public static void main(String[] args) {
		MasterController master = new MasterController();
		ms = master;
		master.start();
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		// selectors buttons test
		for (int i = 0; i < selections.length; i++) {
			if (event.getSource().equals(selections[i])) {
				clearSelections();
				if (selections[i].getBackground().equals(Color.BLUE)) {
					// it is already selected, de-select it.
					selections[i].setBackground(Color.LIGHT_GRAY);
					selections[i].setForeground(Color.BLACK);
					isSelected[i] = false;
					// give the items section to the user
					clearItems();
					selectedNum = -1;
				} else {
					selections[i].setBackground(Color.BLUE);
					selections[i].setForeground(Color.WHITE);
					isSelected[i] = true;
					selectedNum = i;
					// clean the items button slate
					clearItems();
					// give the items section to the user
					showItems(Lists.getEvent(i));
				}
			}
		}
		// items buttons test
		for (int i = 0; i < num; i++) {
			if (event.getSource().equals(items[i]) && (selectedNum != 2 && selectedNum != 0)) { //not collision or preferences
				if (items[i].getBackground().equals(new Color(60, 60, 200))) {
					// it is already selected, de-select it.
					items[i].setBackground(Color.LIGHT_GRAY);
					items[i].setForeground(Color.BLACK);
					selectedItemNum = -1;
				} else {
					items[i].setBackground(new Color(60, 60, 200));
					items[i].setForeground(Color.WHITE);
					selectedItemNum = i;
					// give the new values section to the user
					showValues(i);
				}
			} else if (event.getSource().equals(items[i]) && (selectedNum == 2 && selectedNum != 0)) { //not collisions but preferences
				if (items[i].getBackground().equals(new Color(60, 60, 200))) {
					// it is already selected, de-select it.
					items[i].setBackground(Color.LIGHT_GRAY);
					items[i].setForeground(Color.BLACK);
					selectedItemNum = -1;
				} else {
					items[i].setBackground(new Color(60, 60, 200));
					items[i].setForeground(Color.WHITE);
					selectedItemNum = i;
					// give the new values section to the user
					showPreferences(i);
				}
			} else if (event.getSource().equals(items[i]) && (selectedNum != 2 && selectedNum == 0)) { //not preferences but collisions
				selections[i].setBackground(Color.LIGHT_GRAY);
				selections[i].setForeground(Color.BLACK);
				isSelected[i] = false;
				// give the items section to the user
				selectedNum = 0;
				connection.sendEventToServer("1;" + collisions.getSide(i));
			}
		}
	}
	
	public static MasterController getMasterController() {
		return ms;
	}
	
	public static Connection getConnection() {
		return connection;
	}
	
	public static Addresses getAddress() {
		return addresses;
	}
}
package com.sss.mastercontroller.io;

import javax.swing.table.AbstractTableModel;

import com.sss.mastercontroller.main.MasterController;

/**
 * This class is used only for the IP List, it allows the table to be organized to my liking.
 * @author Bryce Hahn
 * @since 1.0
 */
public class TableModel extends AbstractTableModel {
	private static final long serialVersionUID = -7704884563311411792L;

	private String[] columnNames = { "Index", "IP Addresses", "IP Definition" };
	private Object[][] data;

	public TableModel() {
		data = new Object[MasterController.getAddress().getAddresses()][3];
		for (int i = 0; i < MasterController.getAddress().getAddresses(); i++) {
			data[i][0] = MasterController.getAddress().getIndex(i);
			data[i][1] = MasterController.getAddress().getAddress(i);
			data[i][2] = MasterController.getAddress().getDefinition(i);
		}
	}

	@Override
	public int getColumnCount() {
		return 3;
	}

	@Override
	public int getRowCount() {
		return MasterController.getAddress().getAddresses();
	}

	public String getColumnName(int col) {
		return columnNames[col];
	}

	@Override
	public Object getValueAt(int row, int col) {
		return data[row][col];
	}

	@SuppressWarnings({ "unchecked", "rawtypes" })
	public Class getColumnClass(int c) {
		return getValueAt(0, c).getClass();
	}

	public boolean isCellEditable() {
		return false;
	}
	
	public void setValueAt(Object value, int row, int col) {
		data[row][col] = value;
		fireTableCellUpdated(row, col);
	}
}
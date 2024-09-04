package treeCompare.source;

import java.util.List;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOError;
import java.util.ArrayList;
import treeCompare.data.Star;

public class Read {

	private String filename;
	private String encoding;
	private String lineSplit;

	/**
	 * 
	 * @param filename
	 * @param encoding
	 * @param lineSplit
	 */
	public Read(String filename, String encoding, String lineSplit) {
		this.filename = filename;
		this.encoding = encoding;
		this.lineSplit = lineSplit;
	}

	public List<Star> read() {
		List<Star> stars = new ArrayList<>();

		File file = new File(this.filename);
		Scanner scanner = null;
		try {
			scanner = new Scanner(file, this.encoding);
			while (scanner.hasNext()) {
				String line = scanner.next();
				String[] partOfLines = line.split(this.lineSplit);
				Star star = new Star(Long.parseLong(partOfLines[0]), Double.parseDouble(partOfLines[1]),
						Double.parseDouble(partOfLines[2]), Float.parseFloat(partOfLines[3]),
						Float.parseFloat(partOfLines[4]), Float.parseFloat(partOfLines[5]),
						Float.parseFloat(partOfLines[6]), Float.parseFloat(partOfLines[7]), 0.0);
				stars.add(star);
			}
		} catch (IOError | FileNotFoundException e) {
			System.err.println(e.getMessage());
		} finally {
			scanner.close();
		}

		return stars;
	}

	
	public List<Double> readPoints() {
		List<Double> points = new ArrayList<>();

		File file = new File(this.filename);
		Scanner scanner = null;
		try {
			scanner = new Scanner(file, this.encoding);
			while (scanner.hasNext()) {
				String line = scanner.next();
				
				points.add(Double.parseDouble(line));
			}
		} catch (IOError | FileNotFoundException e) {
			System.err.println(e.getMessage());
		} finally {
			scanner.close();
		}

		return points;
	}
	
}

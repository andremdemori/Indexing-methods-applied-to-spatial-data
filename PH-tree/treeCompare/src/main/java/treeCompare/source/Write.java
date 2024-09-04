package treeCompare.source;

import java.io.File;
import java.io.PrintWriter;
import java.util.List;
import treeCompare.data.Star;

public class Write {

	private String filename;

	/**
	 * @param filename
	 * @param encoding
	 */
	public Write(String filename) {
		this.filename = filename;
	}
	

	public void write(Star star, List<Star> result) {

		File file = new File(this.filename);
		PrintWriter writer = null;

		try {
			writer = new PrintWriter(file);
			writer.write(String.format("%d, %f, %f, %f, %f, %f, %f, %f|", star.getPointId(), star.getRa(),
					star.getDec(), star.getU(), star.getG(), star.getR(), star.getI(), star.getZ()));
			
			for (int i = 0; i < result.size(); i++) {
				writer.write(result.get(i).toString());
			}

		} catch (Exception e) {
			System.err.println(e.getMessage());
		} finally {
			writer.close();
		}
	}

}

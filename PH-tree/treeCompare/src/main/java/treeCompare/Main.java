package treeCompare;

import treeCompare.controller.Application;

public class Main {

	public static void main(String[] args) {
		if (args.length < 4) {
			System.out.println("PhTree:\n\t[1]DatasetFile\n\t[2]PointFile\n\t[3]DistanceFile\n\t[4]Output");
		} else {
			String datasetFile = args[0];
			String pointsFile = args[1];
			String distanceFile = args[2];
			String output = args[3];
			
			Application application = new Application(datasetFile, pointsFile, distanceFile, output);
			application.execute();
		}

	}

}

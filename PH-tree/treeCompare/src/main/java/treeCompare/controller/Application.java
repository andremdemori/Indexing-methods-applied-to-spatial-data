package treeCompare.controller;

import java.util.ArrayList;
import java.util.List;

import treeCompare.data.Star;
import treeCompare.source.Read;
import treeCompare.tree.Tree;
import treeCompare.math.Statistics;
import java.util.concurrent.TimeUnit;

public class Application {

	private String datasetFile;
	private String pointsFile;
	private String distanceFile;
	private String output;

	/**
	 * @param input
	 * @param output
	 * @param output2
	 */
	public Application(String datasetFile, String pointsFile, String distanceFile, String output) {
		this.datasetFile = datasetFile;
		this.distanceFile = distanceFile;
		this.output = output;
		this.pointsFile = pointsFile;
	}

	public void execute() {

		Read read = new Read(datasetFile, "UTF-8", ",");
		Tree tree = new Tree();
		List<Star> stars = read.read();

		long start_buildTree = System.currentTimeMillis();
		for (Star star : stars) {
			tree.insert(star);
		}
		long stop_buildTree = System.currentTimeMillis() - start_buildTree;

		//transformar buildtree para segundos
		String str = "" + stop_buildTree;
		float bt = Float.parseFloat(str);
		bt = bt/1000;
		System.out.println(String.format("BuildTree = %f", bt));


		read = new Read(pointsFile, "UTF-8", ",");
		List<Star> points = read.read();

		read = new Read(distanceFile, "UTF-8", ",");
		List<Double> distance = read.readPoints();



		for (Star star : points) {
				List<Star> n = tree.search(0.680596704877, star);

			System.out.println(
					String.format("Numbers of neighbors: %d",  n.size()));
		}



		/*List<Float> times = new ArrayList<>();
		for (Star star : points) {
			for (Double dist : distance) {
				long start_find = System.currentTimeMillis();
				tree.search(dist, star);
				long stop_find = System.currentTimeMillis();

				long time = stop_find - start_find;

				//transformar tempo de mili para segundos
				String stri = "" + time;
				float to = Float.parseFloat(stri);
				to = to/1000;
				//System.out.printf("Time = %.11f\n", to);

				times.add(to);

			}
			Statistics statistics = new Statistics(times);


			System.out.println(
					String.format("FN : Point ID = %d, Mean = %.25f, var = %.25f", star.getPointId(), statistics.getMean(),
							statistics.getVariance())
			);
		}*/

		/*List<Float> times = new ArrayList<>();
		int count = 1;
		for (Double dist : distance) {
			for (Star star : points) {
				long start_find = System.currentTimeMillis();
				tree.search(dist, star);
				long stop_find = System.currentTimeMillis();

				long time = stop_find - start_find;

				//transformar tempo para segundos
				String stri = "" + time;
				float to = Float.parseFloat(stri);
				to = to/1000;
				//System.out.printf("Time = %f", to);

				times.add(to);
			}
			Statistics statistics = new Statistics(times);

			System.out.println(
					String.format("FN : Dist = %d, Mean = %.25f, var = %.25f", count, statistics.getMean(),
					statistics.getVariance())
			);
			count += 1;
		}*/

	}

}

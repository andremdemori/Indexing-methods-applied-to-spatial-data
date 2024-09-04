package treeCompare.tree;

import ch.ethz.globis.phtree.PhTreeF;
import ch.ethz.globis.phtree.PhTreeF.PhQueryF;
import ch.ethz.globis.phtree.PhTreeF.PhRangeQueryF;

import java.util.ArrayList;
import java.util.List;

import treeCompare.data.Star;
import treeCompare.math.EuclideanDistance;

/**
 * 
 * @author joaonr
 *
 */
public class Tree {

	private PhTreeF<Star> phTreeF;
	private EuclideanDistance euclideanDistance;

	/**
	 * 
	 */
	public Tree() {
		this.phTreeF = PhTreeF.create(2);
		this.euclideanDistance = new EuclideanDistance();
	}

	/**
	 * 
	 * @param star
	 */
	public void insert(Star star) {
		double[] key = new double[2];
		key[0] = star.getRa();
		key[1] = star.getDec();
		phTreeF.put(key, star);
	}

	/**
	 * 
	 * @param distance
	 * @param point
	 * @return
	 */
	public List<Star> search(double distance, Star key) {
		double[] point = new double[2];
		point[0] = key.getRa();
		point[1] = key.getDec();

		List<Star> stars = new ArrayList<>();
		
		PhRangeQueryF<Star> query = phTreeF.rangeQuery(distance, point);

		for (PhRangeQueryF<Star> iterator = query; iterator.hasNext();) {
			Star star = iterator.nextValue();

			//double[] resultStarDouble = new double[2];
			//resultStarDouble[0] = star.getRa();
			//resultStarDouble[1] = star.getDec();

			//double calculatedDistance = euclideanDistance.calculate(point, resultStarDouble);

			//if (star.getDistance() <= distance) {
			//star.setDistance(calculatedDistance);
			stars.add(star);
			//}

		}

		return stars;
	}

}

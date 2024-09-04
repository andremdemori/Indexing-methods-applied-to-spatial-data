package treeCompare.data;

public class Star implements Comparable<Star> {

	private long pointId;
	private double ra;
	private double dec;
	private double distance;
	private float u;
	private float g;
	private float r;
	private float i;
	private float z;

	/**
	 * @param pointId
	 * @param ra
	 * @param dec
	 * @param distance
	 * @param u
	 * @param g
	 * @param r
	 * @param i
	 * @param z
	 */
	public Star(long pointId, double ra, double dec, float u, float g, float r, float i, float z, double distance) {
		this.pointId = pointId;
		this.ra = ra;
		this.dec = dec;
		this.u = u;
		this.g = g;
		this.r = r;
		this.i = i;
		this.z = z;
		this.distance = distance;
	}

	/**
	 * @return the pointId
	 */
	public long getPointId() {
		return pointId;
	}

	/**
	 * @param pointId
	 *            the pointId to set
	 */
	public void setPointId(long pointId) {
		this.pointId = pointId;
	}

	/**
	 * @return the ra
	 */
	public double getRa() {
		return ra;
	}

	/**
	 * @param ra
	 *            the ra to set
	 */
	public void setRa(double ra) {
		this.ra = ra;
	}

	/**
	 * @return the dec
	 */
	public double getDec() {
		return dec;
	}

	/**
	 * @param dec
	 *            the dec to set
	 */
	public void setDec(double dec) {
		this.dec = dec;
	}

	/**
	 * @return the u
	 */
	public float getU() {
		return u;
	}

	/**
	 * @param u
	 *            the u to set
	 */
	public void setU(float u) {
		this.u = u;
	}

	/**
	 * @return the g
	 */
	public float getG() {
		return g;
	}

	/**
	 * @param g
	 *            the g to set
	 */
	public void setG(float g) {
		this.g = g;
	}

	/**
	 * @return the r
	 */
	public float getR() {
		return r;
	}

	/**
	 * @param r
	 *            the r to set
	 */
	public void setR(float r) {
		this.r = r;
	}

	/**
	 * @return the i
	 */
	public float getI() {
		return i;
	}

	/**
	 * @param i
	 *            the i to set
	 */
	public void setI(float i) {
		this.i = i;
	}

	/**
	 * @return the z
	 */
	public float getZ() {
		return z;
	}

	/**
	 * @param z
	 *            the z to set
	 */
	public void setZ(float z) {
		this.z = z;
	}
	
	/**
	 * @return the distance
	 */
	public double getDistance() {
		return distance;
	}

	/**
	 * @param distance
	 *            the distance to set
	 */
	public void setDistance(double distance) {
		this.distance = distance;
	}

	@Override
	public int compareTo(Star star) {
		if (0 < star.getDistance()) {
			return -1;
		} else if (0 > star.getDistance()) {
			return 1;
		}
		return 0;
	}

	@Override
	public String toString() {
		return String.format("%d, %f, %f, %f, %f, %f, %f, %f, %f", pointId, distance, ra, dec, u, g, r, i, z);
	}

}

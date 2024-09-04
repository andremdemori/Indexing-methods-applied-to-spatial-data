package treeCompare.math;

public class EuclideanDistance {
    public double calculate(double[] x1, double[] x2) {
      return Math.sqrt(((x1[1] - x2[1])*(x1[1] - x2[1])) + ((x1[0] - x2[0])*(x1[0] - x2[0])));
  }
}

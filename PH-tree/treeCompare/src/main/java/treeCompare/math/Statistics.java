package treeCompare.math;

import java.util.List;

public class Statistics {
	List<Float> data;
    int size;   

    public Statistics(List<Float> data) {
        this.data = data;
        size = data.size();
    }   

    public double getMean() {       
        double sum = 0.0;
        for(double a : data)
            sum += a;
        return sum/size;
    }

    public double getVariance() {
    	double mean = getMean();
        double temp = 0;
        for(double a :data)
            temp += (a-mean)*(a-mean);
        return temp/size;
    }

    public double getStdDev() {
        return Math.sqrt(getVariance());
    }
}

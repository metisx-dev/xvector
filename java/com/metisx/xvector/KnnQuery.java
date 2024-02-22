package com.metisx.xvector;

public class KnnQuery extends Query implements AutoCloseable {

    static {
        System.loadLibrary("xvector-jni-sim");
    }

    public KnnQuery(Context context, OpType opType, float[] queryVector, int dimension, int k) {
        super(context);

        super.nativeObject = nativeInit(context.nativeObject, opType.getValue(), queryVector, dimension, k);
        context.knnQueries.add(this);
    }

    public void close() {
        if (!closed) {
            nativeClose(nativeObject);
            context.knnQueries.remove(this);
            closed = true;
        }
    }

    public boolean isClosed() {
        return closed;
    }

    public void setTarget(VectorArray target) {
        VectorArray[] targets = { target };
        setTargets(targets);
    }

    public void setTargets(VectorArray[] targets) {
        long[] nativeTargets = new long[targets.length];
        for (int i = 0; i < targets.length; i++) {
            nativeTargets[i] = targets[i].nativeObject;
        }
        nativeSetTargets(nativeObject, TARGET_VECTOR_ARRAY, nativeTargets);
    }

    public void setTarget(IndexArray target) {
        IndexArray[] targets = { target };
        setTargets(targets);
    }

    public void setTargets(IndexArray[] targets) {
        long[] nativeTargets = new long[targets.length];
        for (int i = 0; i < targets.length; i++) {
            nativeTargets[i] = targets[i].nativeObject;
        }
        nativeSetTargets(nativeObject, TARGET_INDEX_ARRAY, nativeTargets);
    }

    public void setFilter(Filter filter) {
        Filter[] filters = { filter };
        setFilters(filters);
    }

    public void setFilters(Filter[] filters) {
        long[] nativeFilters = new long[filters.length];
        for (int i = 0; i < filters.length; i++) {
            nativeFilters[i] = filters[i].nativeObject;
        }
        nativeSetFilters(nativeObject, nativeFilters);
    }

    public KnnResult getResults() {
        long nativeResult = nativeGetResults(nativeObject);
        return new KnnResult(context, nativeResult);
    }

    private static final int TARGET_VECTOR_ARRAY = 0;
    private static final int TARGET_INDEX_ARRAY = 1;

    private native long nativeInit(long nativeContext, int opType, float[] queryVector,
            int dimension, int k);

    private native void nativeClose(long nativeObject);

    private native void nativeSetTargets(long nativeObject, int targetType, long[] targets);

    private native void nativeSetFilters(long nativeObject, long[] filters);

    private native long nativeGetResults(long nativeObject);

    private boolean closed = false;
}

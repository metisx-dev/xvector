package com.metisx.xvector;

import java.util.ArrayList;

public class Context implements AutoCloseable {

    static {
        System.loadLibrary("xvector-jni-sim");
    }

    public Context() {
        this.nativeObject = nativeInit();
    }

    public void close() {
        if (!closed) {

            while (!knnQueries.isEmpty()) {
                knnQueries.remove(0).close();
            }

            while (!knnResults.isEmpty()) {
                knnResults.remove(0).close();
            }

            while (!indexArrays.isEmpty()) {
                indexArrays.remove(0).close();
            }
            
            while (!vectorArrays.isEmpty()) {
                vectorArrays.remove(0).close();
            }

            // while (!filters.isEmpty()) {
            //     filters.remove(0).close();
            // }

            while (!buffers.isEmpty()) {
                buffers.remove(0).close();
            }

            nativeClose(nativeObject);
            
            closed = true;
        }
    }

    public boolean getClosed() {
        return closed;
    }

    private native long nativeInit();

    private native void nativeClose(long nativeObject);

    long nativeObject;
    private boolean closed = false;

    ArrayList<Buffer> buffers = new ArrayList<Buffer>();
    ArrayList<VectorArray> vectorArrays = new ArrayList<VectorArray>();
    ArrayList<IndexArray> indexArrays = new ArrayList<IndexArray>();
    ArrayList<Filter> filters = new ArrayList<Filter>();
    ArrayList<KnnQuery> knnQueries = new ArrayList<KnnQuery>();
    ArrayList<KnnResult> knnResults = new ArrayList<KnnResult>();
}

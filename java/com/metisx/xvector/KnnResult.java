package com.metisx.xvector;

import java.nio.*;

public class KnnResult implements AutoCloseable {

    static {
        System.loadLibrary("xvector-jni-sim");
    }

    KnnResult(Context context, long nativeObject) {
        this.nativeObject = nativeObject;
        this.context = context;
        context.knnResults.add(this);
    }

    public void close() {
        if (!closed) {
            nativeClose(nativeObject);
            context.knnResults.remove(this);
            closed = true;
        }
    }

    public boolean isClosed() {
        return closed;
    }

    public int getK() {
        return nativeGetK(nativeObject);
    }

    public float[] getScores() {
        return nativeGetScores(nativeObject);
        //ByteBuffer byteBuffer = nativeGetScores(nativeObject);
        //FloatBuffer floatBuffer = byteBuffer.asFloatBuffer();
        //float scores[] = new float[this.getK()];
        //floatBuffer.get(scores);
        //return scores;
        //return floatBuffer.array();
    }

    public int[] getIndices() {
        return nativeGetIndices(nativeObject);
        //ByteBuffer byteBuffer = nativeGetIndices(nativeObject);
        //int[] indices = new int[this.getK()];
        //System.out.println("byteBuffer: " + byteBuffer);
        //IntBuffer intBuffer = byteBuffer.asIntBuffer();
        //System.out.println("intBuffer: " + intBuffer);
        //intBuffer.get(indices);
        //System.out.println("indices: " + indices);
        //return indices;

        //return byteBuffer.asIntBuffer().array();
    }

    public VectorArray[] vectorArrays() {
        return nativeVectorArrays(nativeObject);
    }

    private native void nativeClose(long nativeObject);

    private native int nativeGetK(long nativeObject);

    private native float[] nativeGetScores(long nativeObject);

    private native int[] nativeGetIndices(long nativeObject);

    private native VectorArray[] nativeVectorArrays(long nativeObject);

    Context context;
    long nativeObject;
    private boolean closed = false;
}

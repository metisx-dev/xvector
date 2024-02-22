package com.metisx.xvector;

public class VectorArray implements AutoCloseable {

    static {
        System.loadLibrary("xvector-jni-sim");
    }

    public VectorArray(Context context, int dimension) {
        nativeObject = nativeInit(context.nativeObject, dimension);
        this.context = context;
        context.vectorArrays.add(this);
    }

    public void close() {
        if (!closed) {
            nativeClose(nativeObject);
            context.vectorArrays.remove(this);
            closed = true;
        }
    }

    public boolean isClosed() {
        return closed;
    }

    public int dimension() {
        return nativeDimension(nativeObject);
    }

    public void setBuffer(Buffer buffer, int length) {
        nativeSetBuffer(nativeObject, buffer.nativeObject, length);
        this.buffer = buffer;
        this.length = length;
    }

    public Buffer getBuffer() {
        return buffer;
    }

    public int getLength() {
        return length;
    }

    private native long nativeInit(long nativeContext, int dimension);

    private native void nativeClose(long nativeObject);

    private native int nativeDimension(long nativeObject);

    /**
     * Set the elements of the array.
     * 
     * @param buffer The buffer containing the elements.
     * @param length The number of vectors.
     * 
     */
    private native void nativeSetBuffer(long nativeObject, long nativeBuffer, int length);

    Context context;
    long nativeObject;
    private boolean closed = false;
    private Buffer buffer;
    private int length;
}

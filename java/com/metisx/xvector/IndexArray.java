package com.metisx.xvector;

public class IndexArray implements AutoCloseable {

    static {
        System.loadLibrary("xvector-jni-sim");
    }

    public IndexArray(VectorArray vectorArray) {
        nativeObject = nativeInit(vectorArray.nativeObject);
        this.context = vectorArray.context;
        context.indexArrays.add(this);
    }

    public void close() {
        if (!closed) {
            nativeClose(nativeObject);
            context.indexArrays.remove(this);
            closed = true;
        }
    }

    public boolean isClosed() {
        return closed;
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

    private native long nativeInit(long nativeVectorArray);

    private native void nativeClose(long nativeObject);

    private native void nativeSetBuffer(long nativeObject, long nativeBuffer, int length);

    private native int nativeGetLength(long nativeObject);

    Context context;
    long nativeObject;
    private boolean closed = false;
    private Buffer buffer;
    private int length;
}

package com.metisx.xvector;

public class Filter implements AutoCloseable {

    static {
        System.loadLibrary("xvector-jni-sim");
    }

    public Filter(Context context) {
        nativeObject = nativeInit(context.nativeObject);
        this.context = context;
        context.filters.add(this);
    }

    public void close() {
        if (!closed) {
            nativeClose(nativeObject);
            context.filters.remove(this);
            closed = true;
        }
    }

    public boolean isClosed() {
        return closed;
    }

    public void setBuffer(Buffer buffer, int validCount) {
        nativeSetBuffer(nativeObject, buffer.nativeObject, validCount);
        this.buffer = buffer;
        this.validCount = validCount;
    }

    public Buffer getBuffer() {
        return buffer;
    }

    public int getValidCount() {
        return validCount;
    }

    private native long nativeInit(long nativeContext);

    private native void nativeClose(long nativeObject);

    private native void nativeSetBuffer(long nativeObject, long nativeBuffer, int validCount);

    Context context;
    long nativeObject;
    private boolean closed = false;
    private Buffer buffer;
    private int validCount;
}

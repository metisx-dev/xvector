package com.metisx.xvector;

public class Buffer implements AutoCloseable {

    static {
        System.loadLibrary("xvector-jni-sim");
    }

    public Buffer(Context context, long capacity) {
        nativeObject = nativeInit(context.nativeObject, capacity);
        this.context = context;
        context.buffers.add(this);
    }

    public void close() {
        if (!closed) {
            nativeClose(nativeObject);
            context.buffers.remove(this);
            closed = true;
        }
    }

    public boolean isClosed() {
        return closed;
    }

    public long capacity() {
        return nativeCapacity(nativeObject);
    }

    public void copyHostToBuffer(byte[] src, long offset, long length) {
        nativeCopyHostToBuffer(nativeObject, src, offset, length);
    }

    public void copyHostToBuffer(char[] src, long offset, long length) {
        throw new UnsupportedOperationException("Not implemented");
        /// nativeCopyHostToBuffer(nativeObject, src, offset, length);
    }

    public void copyHostToBuffer(short[] src, long offset, long length) {
        throw new UnsupportedOperationException("Not implemented");
        //nativeCopyHostToBuffer(nativeObject, src, offset, length);
    }

    public void copyHostToBuffer(int[] src, long offset, long length) {
        //throw new UnsupportedOperationException("Not implemented");
        nativeCopyHostToBuffer(nativeObject, src, offset, length);
    }

    public void copyHostToBuffer(long[] src, long offset, long length) {
        throw new UnsupportedOperationException("Not implemented");
        // nativeCopyHostToBuffer(nativeObject, src, offset, length);
    }

    public void copyHostToBuffer(float[] src, long offset, long length) {
        nativeCopyHostToBuffer(nativeObject, src, offset, length);
    }

    public void copyHostToBuffer(double[] src, long offset, long length) {
        throw new UnsupportedOperationException("Not implemented");
        // nativeCopyHostToBuffer(nativeObject, src, offset, length);
    }

    public void copyBufferToHost(byte[] dst, long offset, long length) {
        nativeCopyBufferToHost(nativeObject, dst, offset, length);
    }

    public void copyBufferToHost(char[] dst, long offset, long length) {
        throw new UnsupportedOperationException("Not implemented");
        // nativeCopyBufferToHost(nativeObject, dst, offset, length);
    }

    public void copyBufferToHost(short[] dst, long offset, long length) {
        throw new UnsupportedOperationException("Not implemented");
        // nativeCopyBufferToHost(nativeObject, dst, offset, length);
    }

    public void copyBufferToHost(int[] dst, long offset, long length) {
        //throw new UnsupportedOperationException("Not implemented");
         nativeCopyBufferToHost(nativeObject, dst, offset, length);
    }

    public void copyBufferToHost(long[] dst, long offset, long length) {
        throw new UnsupportedOperationException("Not implemented");
        // nativeCopyBufferToHost(nativeObject, dst, offset, length);
    }

    public void copyBufferToHost(float[] dst, long offset, long length) {
        nativeCopyBufferToHost(nativeObject, dst, offset, length);
    }

    public void copyBufferToHost(double[] dst, long offset, long length) {
        throw new UnsupportedOperationException("Not implemented");
        // nativeCopyBufferToHost(nativeObject, dst, offset, length);
    }

    private native long nativeInit(long nativeContext, long capacity);

    private native void nativeClose(long nativeObject);

    private native long nativeCapacity(long nativeObject);

    private native void nativeCopyHostToBuffer(long nativeObject, byte[] src, long offset, long length);

    private native void nativeCopyHostToBuffer(long nativeObject, char[] src, long offset, long length);

    private native void nativeCopyHostToBuffer(long nativeObject, short[] src, long offset, long length);

    private native void nativeCopyHostToBuffer(long nativeObject, int[] src, long offset, long length);

    private native void nativeCopyHostToBuffer(long nativeObject, long[] src, long offset, long length);

    private native void nativeCopyHostToBuffer(long nativeObject, float[] src, long offset, long length);

    private native void nativeCopyHostToBuffer(long nativeObject, double[] src, long offset, long length);

    private native void nativeCopyBufferToHost(long nativeObject, byte[] dst, long offset, long length);

    private native void nativeCopyBufferToHost(long nativeObject, char[] dst, long offset, long length);

    private native void nativeCopyBufferToHost(long nativeObject, short[] dst, long offset, long length);

    private native void nativeCopyBufferToHost(long nativeObject, int[] dst, long offset, long length);

    private native void nativeCopyBufferToHost(long nativeObject, long[] dst, long offset, long length);

    private native void nativeCopyBufferToHost(long nativeObject, float[] dst, long offset, long length);

    private native void nativeCopyBufferToHost(long nativeObject, double[] dst, long offset, long length);

    Context context;
    long nativeObject;
    private boolean closed = false;
}

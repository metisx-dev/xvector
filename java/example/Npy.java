//package com.github.dreamolight.jnpy;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class Npy {
	private byte[] data = null;
	private NpyHeader header;

	public Npy(String path) throws IOException {
		File f = new File(path);
		FileInputStream fis = new FileInputStream(f);
		process(fis);
	}

	public Npy(InputStream inputStream) throws IOException {
		process(inputStream);
	}

	private void process(InputStream inputStream) throws IOException {
		int length = inputStream.available();

		DataInputStream dataIs = new DataInputStream(inputStream);
		byte[] allData = new byte[length];
		dataIs.readFully(allData);
		dataIs.close();
		String magic = new String(allData, 1, 5);
		if (!magic.equals("NUMPY") || (allData[0] & 0xFF) != 0x93) {
			throw new IOException("Invalid prefix");
		}

		int major = allData[6];
		int minor = allData[7];

		if (major != 1 && major != 2) {
			throw new IOException("Invalid jaor version: " + major);
		}

		if (minor != 0)
			throw new IOException("Invalid minor version: " + minor);

		int headerLen;
		int offset;
		if (1 == major) {
			byte[] arr = { allData[8], allData[9] };
			ByteBuffer wrapped = ByteBuffer.wrap(arr);
			wrapped.order(ByteOrder.LITTLE_ENDIAN);

			headerLen = wrapped.getShort();

			offset = 10;
		} else {
			byte[] arr = { allData[8], allData[9], allData[10], allData[11] };
			ByteBuffer wrapped = ByteBuffer.wrap(arr);
			wrapped.order(ByteOrder.LITTLE_ENDIAN);

			headerLen = wrapped.getInt();

			offset = 12;
		}
		int dataLen = length - offset - headerLen;

		byte[] headerData = new byte[headerLen];
		data = new byte[dataLen];

		System.arraycopy(allData, offset, headerData, 0, headerLen);
		System.arraycopy(allData, offset + headerLen, data, 0, dataLen);

		header = NpyHeader.getNpyHeader(headerData);
	}

	public boolean getIsFortranOrder() {
		return header.isFortranOrder;
	}

	public Endian getEndian() {
		return header.endian;
	}

	public DataType getDataType() {
		return header.dataType;
	}

	public float[] floatElements() {
		ByteBuffer wrapped = ByteBuffer.wrap(data);
		wrapped.order(this.getEndian() == Endian.little ? ByteOrder.LITTLE_ENDIAN : ByteOrder.BIG_ENDIAN);

		float[] elements = new float[data.length / 4];

		for (int i = 0; i < elements.length; i++) {
			elements[i] = wrapped.getFloat();
		}

		return elements;
	}

	public double[] doubleElements() {
		ByteBuffer wrapped = ByteBuffer.wrap(data);
		wrapped.order(this.getEndian() == Endian.little ? ByteOrder.LITTLE_ENDIAN : ByteOrder.BIG_ENDIAN);

		double[] elements = new double[data.length / 8];

		for (int i = 0; i < elements.length; i++) {
			elements[i] = wrapped.getDouble();
		}

		return elements;
	}

	public int[] uint16Elements() {
		ByteBuffer wrapped = ByteBuffer.wrap(data);
		wrapped.order(this.getEndian() == Endian.little ? ByteOrder.LITTLE_ENDIAN : ByteOrder.BIG_ENDIAN);

		int[] elements = new int[data.length / 2];

		for (int i = 0; i < elements.length; i++) {
			elements[i] = wrapped.getShort() & 0xffff;
		}

		return elements;
	}

	public int[] int32Elements() {
		ByteBuffer wrapped = ByteBuffer.wrap(data);
		wrapped.order(this.getEndian() == Endian.little ? ByteOrder.LITTLE_ENDIAN : ByteOrder.BIG_ENDIAN);

		int[] elements = new int[data.length / 4];

		for (int i = 0; i < elements.length; i++) {
			elements[i] = wrapped.getInt();
		}

		return elements;
	}
}
#include <assert.h>
#include <xvector/xvector.h>

int main()
{
    xvecStatus status;

    xvecContext context;
    status = xvecCreateContext(&context);
    if (status != XVEC_SUCCESS)
    {
        return status;
    }

    xvecVectorArray vectorArray;
    status = xvecCreateVectorArray(&vectorArray, context, 256);
    if (status != XVEC_SUCCESS)
    {
        return status;
    }

    xvecReleaseVectorArray(vectorArray);

    xvecDestroyContext(context);

    return 0;
}

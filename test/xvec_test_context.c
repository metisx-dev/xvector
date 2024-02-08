#include <assert.h>
#include <xvector/xvector.h>

int main()
{
    xvecContext context;
    xvecStatus status = xvecCreateContext(&context);

    if (status != XVEC_SUCCESS)
    {
        return 1;
    }

    xvecDestroyContext(context);

    return 0;
}

#ifndef __PREPROCESSING_H_
#define __PREPROCESSING_H_

#include <stdint.h>

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif /* UNUSED */

#ifndef UNUSED_PARAM
#define UNUSED_PARAM __attribute__((unused))
#endif /* UNUSED_PARAM */

#ifndef SAFE_FREE
#define SAFE_FREE(x) if (x != NULL) { free(x); x = NULL; }
#endif /* SAFE_FREE */

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) if (x != NULL) { delete x; x = NULL; }
#endif /* SAFE_DELETE */

#ifndef SAFE_CLOSE
#define SAFE_CLOSE(fd) if (fd > 0) { ::close(fd); fd = -1; }
#endif /* SAFE_CLOSE */

#endif /* __PREPROCESSING_H_ */

/* By YZBruh */

/**
 * Copyright 2024 Partition Manager
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <mntent.h>
#include <malloc.h>

ssize_t getrandom(void* buf, size_t buflen, unsigned int flags) {
	if (!buf || buflen == 0) {
		errno = EINVAL;
		return -1;
	}

	const char* device = (flags & 1) ? "/dev/random" : "/dev/urandom";
	int fd = open(device, O_RDONLY);
	if (fd < 0) {
		perror("Failed to open random device");
		return -1;
	}

	ssize_t total_read = 0;
	while (total_read < (ssize_t)buflen) {
		ssize_t bytes_read = read(fd, (char*)buf + total_read, buflen - total_read);
		if (bytes_read < 0) {
			if (errno == EINTR) continue;
			perror("Failed to read random data");
			close(fd);
			return -1;
		}
		total_read += bytes_read;
	}

	close(fd);
	return total_read;
}

int getentropy(void* buf, size_t buflen) {
	if (!buf || buflen == 0 || buflen > 256) {
		errno = EINVAL;
		return -1;
	}

	int fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0) {
		perror("Failed to open /dev/urandom");
		return -1;
	}

	ssize_t total_read = 0;
	while (total_read < (ssize_t)buflen) {
		ssize_t bytes_read = read(fd, (char*)buf + total_read, buflen - total_read);
		if (bytes_read < 0) {
			if (errno == EINTR) continue;
			perror("Failed to read random data");
			close(fd);
			return -1;
		}
		total_read += bytes_read;
	}

	close(fd);
	return 0;
}

char* _Nullable hasmntopt(const struct mntent* mnt, const char* opt) {
	if (!mnt || !opt) return NULL;

	char* options = mnt->mnt_opts;
	size_t opt_len = strlen(opt);

	while (*options) {
		char *comma = strchr(options, ',');
		size_t len = comma ? (size_t)(comma - options) : strlen(options);

		if (len == opt_len && strncmp(options, opt, len) == 0)
			return (char*)options;

		if (!comma) break;
		options = comma + 1;
	}

	return NULL;
}

void* _Nullable reallocarray(void* ptr, size_t count, size_t size) {
	if (count == 0 || size == 0) {
		free(ptr);
		return NULL;
	}

	if (count > SIZE_MAX / size) return NULL;

	size_t total_size = count * size;
	void* new_ptr = realloc(ptr, total_size);
	if (new_ptr == NULL) return NULL;

	return new_ptr;
}

#ifdef __cplusplus
}
#endif

/* end of code */
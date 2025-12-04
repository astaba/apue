#!/bin/bash

# Define the C template content. We use 'BUFFSIZE_PLACEHOLDER'
# to mark the line that needs to be replaced by sed.
C_TEMPLATE=$(
	cat <<_EOF_
#include "../include/apue.h"

#define BUFFSIZE BUFFSIZE_PLACEHOLDER

int main(void) {
	int n;
	char buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);
}
_EOF_
)

# Iterate from 2^0 (1) up to 2^19 (524288)
for ((i = 0; i < 20; i++)); do
	BUFFSIZE=$((1 << i))
	SUFFIX=$(printf '%06d' $BUFFSIZE)
	FILENAME="test_${SUFFIX}.c"

	# Use sed to replace the placeholder with the current buffer size
	echo "$C_TEMPLATE" | sed "s/BUFFSIZE_PLACEHOLDER/${BUFFSIZE}/" >"$FILENAME"
	echo "Generated $FILENAME (Buffer: $BUFFSIZE bytes)"
done

echo "---"
echo "Source files generated successfully."

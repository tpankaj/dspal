/****************************************************************************
 *   Copyright (c) 2015 James Wilson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name ATLFlight nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <dev_fs_lib_i2c.h>
#include <test_status.h>

#include <platform.h>
/**
* @brief Test to see i2c device can be opened and configured.
*
* @par
* Test:
* 1) Open the i2c device (/dev/i2c-8)
* 2) Configure the i2c device to have (using ioctl):
*     -Slave address: 0x70
*     -Bus Frequency in khz: 400
*     -Transfer timeout in usec: 9000
* 3) Close the i2c device
*
* @return
* SUCCESS ------ Test Passes
* ERROR ------ Test Failed
*/
int dspal_tester_i2c_test(void)
{
	int ret = SUCCESS;
	/*
	 * Open i2c device
	 */
	int fd = -1;
	fd = open(I2C_DEVICE_PATH, 0);

	if (fd > 0) {
		/*
		 * Configure I2C device
		 */
		struct dspal_i2c_ioctl_slave_config slave_config;
		slave_config.slave_address = 0x70;
		slave_config.bus_frequency_in_khz = 400;
		slave_config.byte_transer_timeout_in_usecs = 9000;

		if (ioctl(fd, I2C_IOCTL_CONFIG, &slave_config) != 0) {
			ret = ERROR;
		}

		/*
		 * Close the device ID
		 */
		close(fd);

	} else {
		ret = ERROR;
	}

	return ret;
}

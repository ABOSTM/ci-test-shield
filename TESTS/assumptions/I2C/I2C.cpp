// check if I2C is supported on this device
#if !DEVICE_I2C
  #error [NOT_SUPPORTED] I2C not supported on this platform, add 'DEVICE_I2C' definition to your platform.
#endif

#include "mbed.h"
#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"


using namespace utest::v1;

template <PinName d_pin>
void test_I2C_NC()
{
    TEST_ASSERT_MESSAGE(d_pin != NC, "Pin is NC");
}

utest::v1::status_t test_setup(const size_t number_of_cases)
{
    // Setup Greentea using a reasonable timeout in seconds
    GREENTEA_SETUP(5, "default_auto");
    return verbose_test_setup_handler(number_of_cases);
}

utest::v1::status_t greentea_failure_handler(const Case* const source, const failure_t reason)
{
    greentea_case_failure_abort_handler(source, reason);
    return STATUS_CONTINUE;	
}

Case cases[] = {
    Case("I2C - is SDA connected?", test_I2C_NC<MBED_CONF_APP_I2C_SDA>, greentea_failure_handler),
    Case("I2C - is SCL connected?", test_I2C_NC<MBED_CONF_APP_I2C_SCL>, greentea_failure_handler),

};

Specification specification(test_setup, cases);

int main() {
    return !Harness::run(specification);
}

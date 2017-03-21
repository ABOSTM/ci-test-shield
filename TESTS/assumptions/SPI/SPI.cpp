// check if SPI is supported on this device
#if !DEVICE_SPI
    #error [NOT_SUPPORTED] SPI is not supported on this platform, add 'DEVICE_SPI' definition to your platform.
#endif

#include "mbed.h"
#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"


using namespace utest::v1;

template <PinName d_pin>
void test_SPI_NC()
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
    Case("SPI - is MOSI connected?", test_SPI_NC<MBED_CONF_APP_SPI_MOSI>, greentea_failure_handler),
    Case("SPI - is MISO connected?", test_SPI_NC<MBED_CONF_APP_SPI_MISO>, greentea_failure_handler),
    Case("SPI - is SCLK connected?", test_SPI_NC<MBED_CONF_APP_SPI_CLK>, greentea_failure_handler),
    Case("SPI - is nCS  connected?", test_SPI_NC<MBED_CONF_APP_SPI_CS>, greentea_failure_handler),

};

Specification specification(test_setup, cases);

int main() {
    return !Harness::run(specification);
}

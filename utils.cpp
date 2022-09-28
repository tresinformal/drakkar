

void test_utils()
{
    assert(are_equal(0.0, 0.0));
    assert(!are_equal(0.0, 0.1));
    assert(!are_equal(0.00001, 0.00002, 0.000001));
    assert(are_equal(0.0001, 0.0002, 0.001));
}

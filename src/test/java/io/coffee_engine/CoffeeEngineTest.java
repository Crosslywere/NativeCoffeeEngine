package io.coffee_engine;

import org.junit.Assert;
import org.junit.Test;

public class CoffeeEngineTest {

    @Test
    public void SimpleTest() {
        Assert.assertTrue(CoffeeEngine.Test());
    }

    @Test
    public void TestVulkan() {
        Assert.assertTrue(CoffeeEngine.TestVulkan());
    }
}

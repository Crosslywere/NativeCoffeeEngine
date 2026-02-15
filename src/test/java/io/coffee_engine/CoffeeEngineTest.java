package io.coffee_engine;

import org.junit.Assert;
import org.junit.Test;

import io.coffee_engine.test.TestUtil;

public class CoffeeEngineTest {

    @Test
    public void TestOpenGL() {
        Assert.assertTrue(TestUtil.TestOpenGL());
    }

    @Test
    public void TestVulkan() {
        Assert.assertTrue(TestUtil.TestVulkan());
    }
}

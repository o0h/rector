<?php

namespace spec\Rector\PhpSpecToPHPUnit\Tests\Rector\MethodCall\PhpSpecToPHPUnitRector\Fixture;

use Rector\PhpSpecToPHPUnit\Tests\Rector\Class_\PhpSpecToPHPUnitRector\Source\DummyObjectBehavior;

class RatesSpec extends DummyObjectBehavior
{
    public function let(Provider $provider)
    {
        $provider->get()->shouldBeCalled()->willReturn(
            '08.12.2017 #237
            země|měna|množství|kód|kurz
            Austrálie|dolar|1|AUD|16,362
            Velká Británie|libra|1|GBP|29,194'
        );
        $this->beConstructedWith($provider);
    }

    public function it_is_initializable()
    {
        $this->shouldHaveType(Rates::class);
    }

    public function it_should_load_current_rates(Provider $provider)
    {
        $provider->get()->shouldBeCalled()->willReturn(
            '08.12.2017 #237
            země|měna|množství|kód|kurz
            Austrálie|dolar|1|AUD|16,362
            Velká Británie|libra|1|GBP|29,194'
        );

        $this->load()->shouldReturnRates(new ArrayCollection([
            new Rate('AUD', '16.362'),
            new Rate('GBP', '29.194'),
        ]));
    }

    public function getMatchers(): array
    {
        return [
            'returnRates' => function (ArrayCollection $rates, ArrayCollection $expectedRates) {
                foreach ($rates as $index => $rate) {
                    if ($rate->rate !== $expectedRates[$index]->rate || $rate->currency !== $expectedRates[$index]->currency) {
                        return false;
                    }
                }

                return true;
            },
        ];
    }
}

?>
-----
<?php

namespace Tests\Rector\PhpSpecToPHPUnit\Tests\Rector\MethodCall\PhpSpecToPHPUnitRector\Fixture;

use Rector\PhpSpecToPHPUnit\Tests\Rector\Class_\PhpSpecToPHPUnitRector\Source\DummyObjectBehavior;

class RatesTest extends \PHPUnit\Framework\TestCase
{
    /**
     * @var \Rector\PhpSpecToPHPUnit\Tests\Rector\MethodCall\PhpSpecToPHPUnitRector\Fixture\Rates
     */
    private $rates;
    protected function setUp()
    {
        /** @var Provider|\PHPUnit\Framework\MockObject\MockObject $provider */
        $provider = $this->createMock(Provider::class);
        $provider->expects($this->once())->method('get')->willReturn(
            '08.12.2017 #237
            země|měna|množství|kód|kurz
            Austrálie|dolar|1|AUD|16,362
            Velká Británie|libra|1|GBP|29,194'
        );
        $this->rates = new \Rector\PhpSpecToPHPUnit\Tests\Rector\MethodCall\PhpSpecToPHPUnitRector\Fixture\Rates($provider);
    }

    public function testInitializable()
    {
        $this->assertInstanceOf(Rates::class, $this->rates);
    }

    public function testLoadCurrentRates()
    {
        /** @var Provider|\PHPUnit\Framework\MockObject\MockObject $provider */
        $provider = $this->createMock(Provider::class);
        $provider->expects($this->once())->method('get')->willReturn(
            '08.12.2017 #237
            země|měna|množství|kód|kurz
            Austrálie|dolar|1|AUD|16,362
            Velká Británie|libra|1|GBP|29,194'
        );
        $matcherCallable = $this->getMatchers()['returnRates'];
        $matcherCallable(new ArrayCollection([
            new Rate('AUD', '16.362'),
            new Rate('GBP', '29.194'),
        ]), $this->rates->load());
    }

    public function getMatchers(): array
    {
        return [
            'returnRates' => function (ArrayCollection $rates, ArrayCollection $expectedRates) {
                foreach ($rates as $index => $rate) {
                    if ($rate->rate !== $expectedRates[$index]->rate || $rate->currency !== $expectedRates[$index]->currency) {
                        return false;
                    }
                }

                return true;
            },
        ];
    }
}

?>

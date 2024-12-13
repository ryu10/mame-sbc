// license:BSD-3-Clause
// copyright-holders: Norihiro Kumagai

// Blink ... LED-tikker (L-chika) device

#include "blink.h"
#include "attotime.h"

// device type definitions
DEFINE_DEVICE_TYPE(BLINK, blink_device, "blink", "LED blinking")

blink_device::blink_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, u32 clock)
	: device_t(mconfig, type, tag, owner, clock)
	, m_output_cb(*this)
	, m_periodic_timer(nullptr)
	, m_phase(0)
{
}

blink_device::blink_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock)
	: blink_device(mconfig, BLINK, tag, owner, clock)
{
}


#define BLINK_PERIOD 500

void blink_device::device_start()
{
	// Create timer
	fprintf(stderr, "blink_device::device_start\n");
	m_periodic_timer = timer_alloc(FUNC(blink_device::periodic_update), this);
}

void blink_device::device_reset()
{
	// Output delay from reset
	fprintf(stderr, "blink_device::device_reset\n");
	m_periodic_timer->adjust(attotime::from_msec(BLINK_PERIOD));
}

TIMER_CALLBACK_MEMBER(blink_device::periodic_update)
{
	// Up to four different phases
	m_phase = (m_phase + 1) & 3;
	m_output_cb(BIT(m_phase, 0));
	m_periodic_timer->adjust(attotime::from_msec(BLINK_PERIOD));
}


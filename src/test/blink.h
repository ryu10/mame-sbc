// license:BSD-3-Clause
// copyright-holders: Norihiro Kumagai

// Blink ... LED-tikker (L-chika) devuce

#ifndef MAME_BLINK_DEVICE_H
#define MAME_BLINK_DEVICE_H

#pragma once

#include "emu.h"
#include "schedule.h"
#include "osdcomm.h"
#include "devcb.h"

class blink_device : public device_t
{
public:
    blink_device(const machine_config &mconfig, const char *tag, device_t *owner, u32 clock);
    auto output_cb() { return m_output_cb.bind(); }
protected:
	// base class constructor
    blink_device(
		const machine_config &mconfig, 
		device_type type, 
		const char *tag, 
		device_t *owner, 
		u32 clock);

	// device_t implementation
	virtual void device_start() override ATTR_COLD;
	virtual void device_reset() override ATTR_COLD;
private:
	// timed update callback
	TIMER_CALLBACK_MEMBER(periodic_update);
	// callbacks
	devcb_write_line m_output_cb;
	// timer
	emu_timer *m_periodic_timer;
	// internal state
	int m_phase;
};

DECLARE_DEVICE_TYPE(BLINK, blink_device)
#endif /* MAME_BLINK_DEVICE_H */

/*
 * Copyright (c) 2010 ARM Limited
 * All rights reserved
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Ali Saidi
 */

#include "base/trace.hh"
#include "dev/arm/rv_ctrl.hh"
#include "mem/packet.hh"
#include "mem/packet_access.hh"

RealViewCtrl::RealViewCtrl(Params *p)
    : BasicPioDevice(p)
{
    pioSize = 0xD4;
}

Tick
RealViewCtrl::read(PacketPtr pkt)
{
    assert(pkt->getAddr() >= pioAddr && pkt->getAddr() < pioAddr + pioSize);
    assert(pkt->getSize() == 4);
    Addr daddr = pkt->getAddr() - pioAddr;
    pkt->allocate();

    switch(daddr) {
      case ProcId:
        pkt->set(params()->proc_id);
        break;
      case Clock24:
        Tick clk;
        clk = (Tick)(curTick / (24 * SimClock::Float::MHz));
        pkt->set((uint32_t)(clk));
        break;
      case Flash:
        pkt->set<uint32_t>(0);
        break;
      default:
        panic("Tried to read RealView I/O at offset %#x that doesn't exist\n", daddr);
        break;
    }
    pkt->makeAtomicResponse();
    return pioDelay;

}

Tick
RealViewCtrl::write(PacketPtr pkt)
{
    assert(pkt->getAddr() >= pioAddr && pkt->getAddr() < pioAddr + pioSize);

    Addr daddr = pkt->getAddr() - pioAddr;
    switch (daddr) {
      case Flash:
        break;
      default:
        panic("Tried to write RVIO at offset %#x that doesn't exist\n", daddr);
        break;
    }
    pkt->makeAtomicResponse();
    return pioDelay;
}

void
RealViewCtrl::serialize(std::ostream &os)
{
}

void
RealViewCtrl::unserialize(Checkpoint *cp, const std::string &section)
{
}

RealViewCtrl *
RealViewCtrlParams::create()
{
    return new RealViewCtrl(this);
}

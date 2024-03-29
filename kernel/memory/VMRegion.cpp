/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright © 2016-2022 Byteduck */

#include "VMRegion.h"
#include "MemoryManager.h"

VMProt VMProt::R = {
		.read = true,
		.write = false,
		.execute = false,
		.cow = false
};

VMProt VMProt::RW = {
		.read = true,
		.write = true,
		.execute = false,
		.cow = false
};

VMProt VMProt::RX = {
		.read = true,
		.write = false,
		.execute = true,
		.cow = false
};

VMProt VMProt::RWX = {
		.read = true,
		.write = true,
		.execute = true,
		.cow = false
};

VMRegion::VMRegion(kstd::Arc<VMObject> object, kstd::Arc<VMSpace> space, size_t start, size_t size, VMProt prot):
	m_object(object),
	m_space(space),
	m_start(start),
	m_size(size),
	m_prot(prot)
{

}

VMRegion::~VMRegion() {
	m_space.with_locked([&](const kstd::Arc<VMSpace>& space) {
		auto unmap_res = space->unmap_region(*this);
		ASSERT(unmap_res.is_success());
	});
}

void VMRegion::set_cow(bool cow) {
	m_prot.cow = cow;
}

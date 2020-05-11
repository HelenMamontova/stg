/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "RFC1213-MIB"
 * 	found in "RFC1213-MIB.asn1"
 * 	`asn1c -fskeletons-copy`
 */

#include <asn_internal.h>

#include "IpRouteEntry.h"

static asn_TYPE_member_t asn_MBR_IpRouteEntry_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteDest),
		(ASN_TAG_CLASS_APPLICATION | (0 << 2)),
		0,
		&asn_DEF_IpAddress,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteDest"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteIfIndex),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteIfIndex"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteMetric1),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteMetric1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteMetric2),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteMetric2"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteMetric3),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteMetric3"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteMetric4),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteMetric4"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteNextHop),
		(ASN_TAG_CLASS_APPLICATION | (0 << 2)),
		0,
		&asn_DEF_IpAddress,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteNextHop"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteType),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteType"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteProto),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteProto"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteAge),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteAge"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteMask),
		(ASN_TAG_CLASS_APPLICATION | (0 << 2)),
		0,
		&asn_DEF_IpAddress,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteMask"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteMetric5),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteMetric5"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct IpRouteEntry, ipRouteInfo),
		(ASN_TAG_CLASS_UNIVERSAL | (6 << 2)),
		0,
		&asn_DEF_OBJECT_IDENTIFIER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"ipRouteInfo"
		},
};
static ber_tlv_tag_t asn_DEF_IpRouteEntry_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_IpRouteEntry_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, 0, 8 }, /* ipRouteIfIndex at 192 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 2, -1, 7 }, /* ipRouteMetric1 at 194 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 3, -2, 6 }, /* ipRouteMetric2 at 196 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 4, -3, 5 }, /* ipRouteMetric3 at 198 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 5, -4, 4 }, /* ipRouteMetric4 at 200 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 7, -5, 3 }, /* ipRouteType at 204 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 8, -6, 2 }, /* ipRouteProto at 206 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 9, -7, 1 }, /* ipRouteAge at 208 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 11, -8, 0 }, /* ipRouteMetric5 at 212 */
    { (ASN_TAG_CLASS_UNIVERSAL | (6 << 2)), 12, 0, 0 }, /* ipRouteInfo at 215 */
    { (ASN_TAG_CLASS_APPLICATION | (0 << 2)), 0, 0, 2 }, /* ipRouteDest at 190 */
    { (ASN_TAG_CLASS_APPLICATION | (0 << 2)), 6, -1, 1 }, /* ipRouteNextHop at 202 */
    { (ASN_TAG_CLASS_APPLICATION | (0 << 2)), 10, -2, 0 } /* ipRouteMask at 210 */
};
static asn_SEQUENCE_specifics_t asn_SPC_IpRouteEntry_specs_1 = {
	sizeof(struct IpRouteEntry),
	offsetof(struct IpRouteEntry, _asn_ctx),
	asn_MAP_IpRouteEntry_tag2el_1,
	13,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_IpRouteEntry = {
	"IpRouteEntry",
	"IpRouteEntry",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_IpRouteEntry_tags_1,
	sizeof(asn_DEF_IpRouteEntry_tags_1)
		/sizeof(asn_DEF_IpRouteEntry_tags_1[0]), /* 1 */
	asn_DEF_IpRouteEntry_tags_1,	/* Same as above */
	sizeof(asn_DEF_IpRouteEntry_tags_1)
		/sizeof(asn_DEF_IpRouteEntry_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_IpRouteEntry_1,
	13,	/* Elements count */
	&asn_SPC_IpRouteEntry_specs_1	/* Additional specs */
};

/*
 * Generated by asn1c-0.9.28 (http://lionet.info/asn1c)
 * From ASN.1 module "RFC1157-SNMP"
 * 	found in "RFC1157-SNMP.asn1"
 * 	`asn1c -S/mnt/data/software/asn1c/skeletons -fcompound-names -fwide-types`
 */

#include "PDU.h"

static asn_TYPE_member_t asn_MBR_PDU_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct PDU, request_id),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"request-id"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PDU, error_status),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"error-status"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PDU, error_index),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_INTEGER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"error-index"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct PDU, variable_bindings),
		(ASN_TAG_CLASS_UNIVERSAL | (16 << 2)),
		0,
		&asn_DEF_VarBindList,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"variable-bindings"
		},
};
static const ber_tlv_tag_t asn_DEF_PDU_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_PDU_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 0, 0, 2 }, /* request-id */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, -1, 1 }, /* error-status */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 2, -2, 0 }, /* error-index */
    { (ASN_TAG_CLASS_UNIVERSAL | (16 << 2)), 3, 0, 0 } /* variable-bindings */
};
static asn_SEQUENCE_specifics_t asn_SPC_PDU_specs_1 = {
	sizeof(struct PDU),
	offsetof(struct PDU, _asn_ctx),
	asn_MAP_PDU_tag2el_1,
	4,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_PDU = {
	"PDU",
	"PDU",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_PDU_tags_1,
	sizeof(asn_DEF_PDU_tags_1)
		/sizeof(asn_DEF_PDU_tags_1[0]), /* 1 */
	asn_DEF_PDU_tags_1,	/* Same as above */
	sizeof(asn_DEF_PDU_tags_1)
		/sizeof(asn_DEF_PDU_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_PDU_1,
	4,	/* Elements count */
	&asn_SPC_PDU_specs_1	/* Additional specs */
};


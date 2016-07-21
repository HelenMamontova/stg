/*
 *  DB migration from v02 to v03 (firebird)
 */

CREATE DOMAIN DM_TARIFF_CHANGE_POLICY AS  VARCHAR(32) NOT NULL
    CHECK (VALUE IN ('allow', 'to_cheap', 'to_expensive', 'deny'));

ALTER TABLE tb_tariffs ADD change_policy DM_TARIFF_CHANGE_POLICY DEFAULT 'allow';

UPDATE tb_info SET version = 2;

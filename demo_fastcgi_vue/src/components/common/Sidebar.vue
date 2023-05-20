<template>
    <div class="sidebar">
        <el-menu
            class="sidebar-el-menu"
            :default-active="onRoutes"
            :collapse="collapse"
            background-color="#324157"
            text-color="#bfcbd9"
            active-text-color="#20a0ff"
            unique-opened
            router
        >
            <div>
                <template v-for="item in Items">
                    <template v-if="item.subs">
                        <el-submenu :index="item.index" :key="item.index">
                            <template slot="title">
                                <i :class="item.icon"></i>
                                <span slot="title">{{ item.title }}</span>
                            </template>
                            <template v-for="subItem in item.subs">
                                <el-submenu v-if="subItem.subs" :index="subItem.index" :key="subItem.index">
                                    <template slot="title">{{ subItem.title }}</template>
                                    <el-menu-item v-for="(threeItem, i) in subItem.subs" :key="i" :index="threeItem.index">{{
                                        threeItem.title
                                    }}</el-menu-item>
                                </el-submenu>
                                <el-menu-item v-else :index="subItem.index" :key="subItem.index">{{ subItem.title }}</el-menu-item>
                            </template>
                        </el-submenu>
                    </template>
                    <template v-else>
                        <el-menu-item :index="item.index" :key="item.index">
                            <i :class="item.icon"></i>
                            <span slot="title">{{ item.title }}</span>
                        </el-menu-item>
                    </template>
                </template>
            </div>
        </el-menu>
    </div>
</template>

<script>
import bus from '../common/bus';
export default {
    data() {
        return {
            collapse: false,
            roseID: this.$store.getters.getUser.roseID,
            Items: [],
            userListItems: [
                {
                    icon: 'el-icon-lx-home',
                    index: 'dashboard',
                    title: '系统首页'
                },
                {
                    icon: 'el-icon-user',
                    index: 'admin',
                    title: '用户信息管理',
                    subs: [
                        {
                            index: 'personInfo',
                            title: '个人信息'
                        }
                    ]
                },
                {
                    icon: 'el-icon-picture',
                    index: '4',
                    title: '数据监控',
                    subs: [
                        {
                            index: 'dataMonitor',
                            title: '实时数据'
                        }
                    ]
                },
                {
                    icon: 'el-icon-camera-solid',
                    index: 'deviceControl',
                    title: '设备控制'
                },
                {
                    icon: 'el-icon-camera-solid',
                    index: 'systemLog',
                    title: '系统日志'
                },
                {
                    icon: 'el-icon-s-tools',
                    index: 'account',
                    title: '账户安全设置',
                    subs: [
                        {
                            index: 'changePwd',
                            title: '修改密码'
                        }
                    ]
                },
                // {
                //     icon: 'el-icon-lx-warn',
                //     index: '7',
                //     title: '错误处理',
                //     subs: [
                //         {
                //             index: 'permission',
                //             title: '权限测试'
                //         },
                //         {
                //             index: '404',
                //             title: '404页面'
                //         }
                //     ]
                // },
                // {
                //     icon: 'el-icon-lx-redpacket_fill',
                //     index: '/donate',
                //     title: '支持作者'
                // }
            ],

        };
    },
    computed: {
        onRoutes() {
            return this.$route.path.replace('/', '');
        }
    },
    created() {
        //console.log(this.roseID);
        //页面渲染---角色判断---分配功能组件
        if (this.roseID === '0') {
            this.Items = this.studentsItems;
        } else if (this.roseID === '1') {
            this.Items = this.teachersItems;
        } else {
            this.Items = this.adminItems;
        }

        // 通过 Event Bus 进行组件间通信，来折叠侧边栏
        bus.$on('collapse', (msg) => {
            this.collapse = msg;
            bus.$emit('collapse-content', msg);
        });
    }
};
</script>

<style scoped>
.sidebar {
    display: block;
    position: absolute;
    left: 0;
    top: 70px;
    bottom: 0;
    overflow-y: scroll;
}
.sidebar::-webkit-scrollbar {
    width: 0;
}
.sidebar-el-menu:not(.el-menu--collapse) {
    width: 250px;
}
.sidebar > ul {
    height: 100%;
}
</style>
